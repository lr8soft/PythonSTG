#include "TaskEnemy.h"
#include "../XCRender/XCImageHelper.h"
#include "../XCRender/RenderManager.h"
#include "TaskDispatcher.h"
TaskEnemy::TaskEnemy(std::string taskUuid, std::vector<std::string> targetTaskUuid, int repeatTime, int intervalFrame, int waitFrame,
	std::string enemyImage, glm::vec2 dInfo, glm::vec3 sInfo, glm::vec2 sbInfo, glm::vec2 wInfo,
	glm::vec3 iCoord, float v, float mTime,float a, float agle, float agleA, int type, float hp):Task(taskUuid, targetTaskUuid, repeatTime, intervalFrame, waitFrame)
{
	imagePath = enemyImage;
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
	nowLife = hp;
}

void TaskEnemy::TaskInit()
{
	if (!taskIsInit) {
		for (int i = 0; i < targetUUID.size(); i++) {
			TaskDispatcher::addTask(targetUUID[i]);
		}
		auto iterBegin = subUnitGroup.begin();
		auto iterEnd = subUnitGroup.end();
		for (auto unit = iterBegin; unit != iterEnd; unit++) {
			(*unit)->UnitInit();
		}

		XCImageHelper *image = new XCImageHelper(imagePath, true);
		enemyImage = new EnemyObject(image, divideInfo, scaleInfo, standbyInfo, walkInfo,
			NowPosition, velocity, movingTime,acceleration, angle, angleAcceleration, colorType, nowLife);
		enemyImage->Init();
		taskIsInit = true;
	}

	
}

void TaskEnemy::taskSubWork()
{
	if (taskWaitFrame > 0) {
		taskWaitFrame--;
		taskWait = true;
	}
	else {
		taskWait = false;
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
				if ((subUnitGroup.empty() && RenderManager::getInstance()->CheckRenderComplete(taskUUID)) || enemyImage->getIsTerminate())
					taskFinish = true;
				taskNowDurationFrame++;
			}
			taskAccumlateTime++;
		}
		else {
			taskFinish = true;
		}
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
	if (!enemyImage->getIsTerminate()) {
		RenderManager::getInstance()->CleanRenderObject(taskUUID);
	}
	else {
		RenderManager::getInstance()->TerminateBullet(taskUUID);
	}
	
	subUnitGroup.clear();

	if (!haveImageAddInQueue) {
		enemyImage->Release();
		delete enemyImage;
	}
	taskIsInit = false;
}





