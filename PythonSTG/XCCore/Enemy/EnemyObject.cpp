#include "EnemyObject.h"
#include "../XCRender/RenderManager.h"
#include "../XCRender/ParticleHelper.h"
#include <GL3/gl3w.h>
#include "../../XCFrameInfo.h"
#include "../Item/ItemHelper.h"
EnemyObject::EnemyObject(IRenderHelper *ptr, glm::vec2 dInfo, glm::vec3 sInfo, glm::vec2 sbInfo, glm::vec2 wInfo,
	glm::vec3 iCoord, float v, float mTime,float a, float agle, float agleA, int type, float health)
{
	imageHelper = ptr;
	divideInfo = dInfo;
	scaleInfo = sInfo;
	standbyInfo = sbInfo;
	walkInfo = wInfo;
	NowPosition = iCoord;

	velocity = v;
	movingTime = mTime;
	acceleration = a;
	angle = agle;
	angleAcceleration = agleA;

	colorType = type;
	currentHealth = health;

	//set as enemytype
	setCurrentType(EnemyType);
}

void EnemyObject::Init()
{
	if (!isInit) {
		deadEffect = AudioHelper::loadWavFromFile("assets/SE/se_enep00.wav");
		if ((angle == 0 && velocity == 0) || angle == 270.0f || angle == 90.0f) {
			nowTexIndex = standbyInfo[0];
		}
		else {
			nowTexIndex = walkInfo[0];
		}
		isInit = true;
	}

}

void EnemyObject::Render()
{
	if (isInit) {
		timer.Tick();
		float deltaTime = timer.getDeltaFrame();
		float pi = 3.1415926535f;
		if (timer.getAccumlateTime() < movingTime || movingTime < 0.0) {
			NowPosition[0] += velocity * cos(angle / 180.0f * pi) * deltaTime;
			NowPosition[1] += velocity * sin(angle / 180.0f * pi) * deltaTime;
			angle += angleAcceleration * deltaTime;
			velocity += acceleration * deltaTime;
		}
		else {
			angle = 0.0f;
			velocity = 0.0f;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		bool isAnti = false;
		if ((angle == 0 && velocity == 0) || angle == 270.0f || angle == 90.0f) {
			if (nowTexIndex < standbyInfo[1])
				nowTexIndex += 8.0f * deltaTime;
			else
				nowTexIndex = standbyInfo[0];
		}
		else {
			if (nowTexIndex < walkInfo[1])
				nowTexIndex += 8.0f * deltaTime;
			else
				nowTexIndex = walkInfo[0];

			if (angle >= 90.0f && angle <= 270.0f) {
				isAnti = true;
			}
		}

		imageHelper->Render(NowPosition, glm::vec4(1.0f), glm::radians(isAnti ? 180.0f : 0.0f), glm::vec3(0, 1, 0), scaleInfo,
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, divideInfo[0], divideInfo[1], (int)nowTexIndex, colorType));

		glDisable(GL_BLEND);

		float frameWidth = XCFrameInfo::FrameRight, frameHeight = XCFrameInfo::FrameTop;
		float renderWidth = scaleInfo[0] * XCFrameInfo::FrameRight;
		float renderHeight = scaleInfo[1] * XCFrameInfo::FrameTop;
		float renderX = NowPosition[0] * frameWidth, renderY = NowPosition[1] * frameHeight;
		if (renderY - renderHeight > frameHeight || renderY + renderHeight< -frameHeight
			|| renderX - renderWidth  > frameWidth || renderX + renderWidth < -frameWidth) {
			isWorkFinish = true;
		}
	}

}

void EnemyObject::Release()
{
	if (isInit) {	
		imageHelper->Release();
		delete imageHelper;
		isInit = false;
	}

}

glm::vec3 EnemyObject::getNowPosition()
{
	return NowPosition;
}

void EnemyObject::hurtEnemy(float damage)
{
	if (currentHealth - damage > 0) {
		currentHealth -= damage;
	}
	else {
		AudioHelper::playFromBuffer(deadEffect.wavBuffer);
		ParticleHelper* particleGroup = new ParticleHelper;
		particleGroup->addNewParticle(20, 12.0f, 1.0f, 0.6f, glm::vec4(1.0f), NowPosition);
		RenderManager::getInstance()->AddRenderObject(ParticleGroupUuid, particleGroup);

		if (dropItemList != nullptr) {
			for (auto item : *dropItemList) {
				ItemHelper::GenerateItemGroup(NowPosition, item.count, (Item::ItemType)item.type, true);
			}
		}

		currentHealth = 0;
		isWorkFinish = true;
	}
}

void EnemyObject::setDropItem(std::vector<DropItem>* pItem)
{
	dropItemList = pItem;
}
