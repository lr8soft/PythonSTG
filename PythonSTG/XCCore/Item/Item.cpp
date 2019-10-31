#include "Item.h"
#include <GL3/gl3w.h>
#include "../XCRender/XCImageHelper.h"
#include "../../XCFrameInfo.h"
#include "../XCRender/AbsorbParticleHelper.h"
#include "../XCRender/RenderManager.h"

Item::Item(const glm::vec2& generateCoord, ItemType itemType, float v, float a, bool exp)
{
	NowPosition = generateCoord;
	currentType = itemType;
	velocity = v;
	angle = a;
	explodeEffect = exp;

	divideInfo = glm::vec4();
	divideInfo.x = 4;
	divideInfo.y = 5;
	switch (itemType) {
	case ItemType::PointType:
		divideInfo.z = 2;
		divideInfo.w = 5;
		break;
	case ItemType::BombType:
		divideInfo.z = 2;
		divideInfo.w = 1;
		break;
	case ItemType::PowerType:
		divideInfo.z = 1;
		divideInfo.w = 5;
		break;
	case ItemType::FullPowerType:
		divideInfo.z = 2;
		divideInfo.w = 4;
		break;
	case ItemType::LifeType:
		divideInfo.z = 1;
		divideInfo.w = 2;
		break;
	}
	setCurrentType(ObjectType::ItemType);
}

void Item::Init()
{
	if (!isInit) {
		itemImage = new XCImageHelper("assets/Item/item.png", true);
		isInit = true;
	}
}

void Item::Render()
{
	if (isInit) {
		timer.Tick();
		if (explodeEffect && timer.getAccumlateTime() < 0.3f) {
			NowPosition.x += 0.2f * cos(angle / 180.0f * 3.1415926f) * timer.getDeltaFrame();
			NowPosition.y += 0.2f * sin(angle / 180.0f * 3.1415926f) * timer.getDeltaFrame();
		}
		NowPosition.y -= velocity * timer.getDeltaFrame();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		itemImage->Render(glm::vec3(NowPosition, 0.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0, 0, 1), glm::vec3(0.05f),
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, divideInfo.x, divideInfo.y, divideInfo.z, divideInfo.w));
		glDisable(GL_BLEND);

		if (NowPosition.y + 0.1f< -1.0f ) {
			isWorkFinish = true;
		}
	}
}

void Item::Release()
{
	if (isInit) {
		itemImage->Release();
		delete itemImage;

		isInit = false;
	}
}

void Item::checkCollideWithPlayer(CollideHelper * helper)
{
	if (!isWorkFinish) {
		float *pos = helper->getPlayerPosition();
		float x = *(pos), y = *(pos + 1);
		AbsorbParticleHelper* particleHelper = new AbsorbParticleHelper;
		float dist = pow(pow(x - NowPosition.x, 2) + pow(y - NowPosition.y, 2), 0.5f);
		if (dist < 0.1f || y> 0.7f) {
			switch (currentType) {
			case ItemType::PointType:
				helper->addPlayerPoint();
				particleHelper->addNewParticle(9, 14.0f, 1.0f, 0.6f, glm::vec4(0.3, 0.3, 0.8, 1.0f), NowPosition, glm::vec2(x, y));
				break;
			case ItemType::BombType:
				helper->addPlayerBomb();
				particleHelper->addNewParticle(24, 18.0f, 1.0f, 1.0f, glm::vec4(0.0, 0.6, 0.3, 1.0f), NowPosition, glm::vec2(x, y));
				break;
			case ItemType::PowerType:
				helper->addPlayerPower();
				particleHelper->addNewParticle(9, 14.0f, 1.0f, 0.6f, glm::vec4(0.8, 0.01, 0.01, 1.0f), NowPosition, glm::vec2(x, y));
				break;
			case ItemType::FullPowerType:
				particleHelper->addNewParticle(24, 18.0f, 1.0f, 1.0f, glm::vec4(0.8, 0.6, 0.01, 1.0f), NowPosition, glm::vec2(x, y));
				break;
			case ItemType::LifeType:
				helper->addPlayerLife();
				particleHelper->addNewParticle(24, 18.0f, 1.0f, 1.0f, glm::vec4(0.9, 0.01, 0.01, 1.0f), NowPosition, glm::vec2(x, y));
				break;
			}
			RenderManager::getInstance()->AddRenderObject(ParticleGroupUuid, particleHelper);
			isWorkFinish = true;
		}
	}
}
