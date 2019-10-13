#include "TaskEnemy.h"
#include "../XCRender/XCImageHelper.h"
#include "../XCRender/RenderManager.h"
#include "TaskDispatcher.h"
TaskEnemy::TaskEnemy(std::string taskUuid, std::string targetTaskUuid, int repeatTime, int intervalFrame,
	std::string enemyImage, glm::vec2 dInfo, glm::vec3 sInfo, glm::vec2 sbInfo, glm::vec2 wInfo,
	glm::vec3 iCoord, float v, float a, float agle, float agleA, int type, float hp):Task(taskUuid, targetTaskUuid, repeatTime, intervalFrame)
{
	imagePath = enemyImage;
	divideInfo = dInfo;
	scaleInfo = sInfo;
	standbyInfo = sbInfo;
	walkInfo = wInfo;
	NowPosition = iCoord;

	velocity = v;
	acceleration = a;
	angle = agle;
	angleAcceleration = agleA;

	colorType = type;
	nowLife = hp;
}

void TaskEnemy::TaskInit()
{
	if (!taskIsInit) {
		TaskDispatcher::addTask(targetUUID);
		auto iterBegin = subUnitGroup.begin();
		auto iterEnd = subUnitGroup.end();
		for (auto unit = iterBegin; unit != iterEnd; unit++) {
			(*unit)->UnitInit();
		}

		XCImageHelper *image = new XCImageHelper(imagePath, true);
		enemyImage = new EnemyObject(image, divideInfo, scaleInfo, standbyInfo, walkInfo,
			NowPosition, velocity, acceleration, angle, angleAcceleration, colorType);
		enemyImage->Init();
		taskIsInit = true;
	}

	
}

void TaskEnemy::TaskWork()
{
	if (taskNowDurationFrame < taskDurationFrame || taskDurationFrame < 0) {
		if (taskAccumlateTime >= taskIntervalFrame) {
			if (!haveImageAddInQueue) {
				RenderManager::getInstance()->AddRenderObject(taskUUID, enemyImage);
				haveImageAddInQueue = true;
			}
			else {
				NowPosition = enemyImage->getNowPosition();
			}
			auto iterBegin = subUnitGroup.begin();
			auto iterEnd = subUnitGroup.end();
			for (auto unit = iterBegin; unit != iterEnd; unit++) {
				if (!(*unit)->IsAddToQueue()) {
					(*unit)->setBulletInitCoord(NowPosition[0], NowPosition[1], NowPosition[2]);
					(*unit)->UnitWork();
				}
				if ((*unit)->IsAddToQueue()) {//release here
					(*unit)->UnitRelease();
					delete (*unit);
					if (std::next(unit) == subUnitGroup.end()) {
						subUnitGroup.erase(unit);
						break;
					}
					else {
						unit = subUnitGroup.erase(unit);
						iterEnd = subUnitGroup.end();
					}
				}
			}
			if ( (subUnitGroup.empty() && RenderManager::getInstance()->CheckRenderComplete(taskUUID)) || enemyImage->getIsTerminate())
				taskFinish = true;
			taskNowDurationFrame++;
		}
		taskAccumlateTime++;
	}
	else {
		taskFinish = true;
	}
}

void TaskEnemy::TaskRelease()
{
	TaskDispatcher::updateTask(taskUUID, true);
	auto iterBegin = subUnitGroup.begin();
	auto iterEnd = subUnitGroup.end();
	for (auto unit = iterBegin; unit != iterEnd; unit++) {
		(*unit)->UnitRelease();
		delete (*unit);
	}
	RenderManager::getInstance()->CleanRenderObject(taskUUID);
	subUnitGroup.clear();

	if (!haveImageAddInQueue) {
		enemyImage->Release();
		delete enemyImage;
	}
	taskIsInit = false;
}





