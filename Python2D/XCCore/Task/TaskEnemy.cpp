#include "TaskEnemy.h"
#include "../XCRender/XCImageHelper.h"
#include "../XCRender/RenderManager.h"
TaskEnemy::TaskEnemy(std::string uuid, int waitFrame, int workInterval, int repeatTime,
	std::string enemyImage, glm::vec2 dInfo, glm::vec3 sInfo, glm::vec2 sbInfo, glm::vec2 wInfo,
	glm::vec3 iCoord, float v, float a, float agle, float agleA, int type):TaskInsideUnit(uuid, waitFrame, workInterval, repeatTime)
{
	imagePath = enemyImage;
	divideInfo = dInfo;
	scaleInfo = sInfo;
	standbyInfo = sbInfo;
	walkInfo = wInfo;
	initCoord = iCoord;

	velocity = v;
	acceleration = a;
	angle = agle;
	angleAcceleration = agleA;

	colorType = type;
}

void TaskEnemy::UnitInit()
{
	TaskInsideUnit::UnitInit();

	XCImageHelper *image = new XCImageHelper(imagePath, true);
	enemyImage = new EnemyObject(image,divideInfo,scaleInfo,standbyInfo, walkInfo,
		initCoord,velocity, acceleration,  angle, angleAcceleration, colorType);
}

void TaskEnemy::UnitWork()
{
	if (waitFrame > 0) {
		waitFrame--;
	}
	else {
		if (!haveAddToQueue) {
			auto iterBegin = renderObjectGroup.begin();
			auto iterEnd = renderObjectGroup.end();
			for (auto object = iterBegin; object != iterEnd; object++) {
				RenderManager::getInstance()->AddRenderObject(parentUuid, *object);
			}
			RenderManager::getInstance()->AddRenderObject(parentUuid, enemyImage);
			haveAddToQueue = true;
		}
	}
}

void TaskEnemy::UnitRelease()
{
	TaskInsideUnit::UnitRelease();
	enemyImage = nullptr;//auto release by rendermananger
}



