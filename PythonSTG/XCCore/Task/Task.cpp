#include "Task.h"
#include "TaskDispatcher.h"
#include "../XCRender/RenderManager.h"
#include <thread>
Task::Task(std::string taskUuid, std::vector<std::string> uuidForWaitTask, int repeatTime, int intervalFrame, int waitFrame)
{
	taskUUID = taskUuid;
	targetUUID.assign(uuidForWaitTask.begin(), uuidForWaitTask.end());

	taskDurationFrame = repeatTime;
	taskIntervalFrame = intervalFrame;

	taskWaitFrame = waitFrame;
}

void Task::addSubUnit(TaskInsideUnit * unit)
{
	subUnitGroup.push_back(unit);
}

void Task::TaskInit()
{
	if (!taskIsInit) {
		TaskDispatcher::addTask(taskUUID);
		auto iterBegin = subUnitGroup.begin();
		auto iterEnd = subUnitGroup.end();
		for (auto unit = iterBegin; unit != iterEnd; unit++) {
			(*unit)->UnitInit();
		}
		taskIsInit = true;
	}
}

void Task::taskSubWork()
{
	if (taskWaitFrame > 0) {
		taskWaitFrame--;
		taskWait = true;
	}
	else {
		taskWait = false;
		if (taskNowDurationFrame < taskDurationFrame || taskDurationFrame < 0) {
			if (taskAccumlateTime >= taskIntervalFrame) {
				auto iterBegin = subUnitGroup.begin();
				auto iterEnd = subUnitGroup.end();
				for (auto unit = iterBegin; unit != iterEnd; unit++) {
					if (!(*unit)->IsAddToQueue()) {
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
				if (subUnitGroup.empty() && RenderManager::getInstance()->CheckRenderComplete(taskUUID))
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

void Task::TaskWork()
{
	if (taskIsInit) {
		if (targetUUID.empty()) {
			taskSubWork();
			taskWaitForTarget = false;
		}
		else {
			bool isAllTargetFinish = true;
			for (int i = 0; i < targetUUID.size(); i++) {
				bool isTargetFinish = TaskDispatcher::getTaskFinish(targetUUID[i]);
				if (!isTargetFinish) {
					isAllTargetFinish = false;
					taskWaitForTarget = true;
				}
			}
			if (isAllTargetFinish) {
				taskSubWork();
				taskWaitForTarget = false;
			}
		}	
	}
}

void Task::TaskRelease()
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
	taskIsInit = false;
}

bool Task::getTaskFinish()
{
	return taskFinish;
}

bool Task::getTaskInit()
{
	return taskIsInit;
}

bool Task::getIsTaskWaiting()
{
	return taskWait;
}

bool Task::getIsTaskWaitingForTarget()
{
	return taskWaitForTarget;
}

std::string Task::getTaskUUID()
{
	return taskUUID;
}
