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

	ItemDivideInfo = glm::vec4();
	ItemDivideInfo.x = 4;
	ItemDivideInfo.y = 6;

	switch (itemType) {
	case ItemType::PointType:
		ItemDivideInfo.z = 2;
		ItemDivideInfo.w = 5;
		break;
	case ItemType::BombType:
		ItemDivideInfo.z = 2;
		ItemDivideInfo.w = 1;
		break;
	case ItemType::PowerType:
		ItemDivideInfo.z = 1;
		ItemDivideInfo.w = 5;
		break;
	case ItemType::FullPowerType:
		ItemDivideInfo.z = 2;
		ItemDivideInfo.w = 4;
		break;
	case ItemType::LifeType:
		ItemDivideInfo.z = 1;
		ItemDivideInfo.w = 2;
		break;
	case ItemType::MoonPointType:
		ItemDivideInfo.z = 1;
		ItemDivideInfo.w = 6;
		break;
	case ItemType::MoonPointMirror:
		ItemDivideInfo.z = 2;
		ItemDivideInfo.w = 6;
		break;
	case ItemType::MoonPointUp:
		ItemDivideInfo.z = 3;
		ItemDivideInfo.w = 6;
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
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, ItemDivideInfo.x, ItemDivideInfo.y, ItemDivideInfo.z, ItemDivideInfo.w));
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
		if (dist < 0.1f || y> 0.65f || helper->getPlayerIsMoonState()) {
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

			case ItemType::MoonPointType:
			case ItemType::MoonPointMirror:
			case ItemType::MoonPointUp:
				helper->addPlayerMoonPoint();
				particleHelper->addNewParticle(9, 14.0f, 1.0f, 0.6f, glm::vec4(0.3, 0.3, 1.0, 1.0f), NowPosition, glm::vec2(x, y));
				break;

			default:
				break;
			}
			RenderManager::getInstance()->AddRenderObject(ParticleGroupUuid, particleHelper);
			isWorkFinish = true;
		}
	}
}
