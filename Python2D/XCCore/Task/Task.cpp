#include "Task.h"
#include "TaskDispatcher.h"

Task::Task(std::string taskUuid, std::string uuidForWaitTask, int repeatTime, int intervalFrame)
{
	taskUUID = taskUuid;
	targetUUID = uuidForWaitTask;

	taskDurationFrame = repeatTime;
	taskIntervalFrame = intervalFrame;
}

void Task::addSubUnit(TaskInsideUnit * unit)
{
	subUnitGroup.push_back(unit);

}

void Task::TaskInit()
{
	if (!taskIsInit) {
		TaskDispatcher::addTask(targetUUID);
		taskIsInit = true;
	}
}

void Task::taskSubWork()
{
	if (taskNowDurationFrame < taskDurationFrame || taskDurationFrame < 0) {
		if (taskAccumlateTime >= taskIntervalFrame) {
			auto iterBegin = subUnitGroup.begin();
			auto iterEnd = subUnitGroup.end();
			for (auto unit = iterBegin; unit != iterEnd; unit++) {
				if (!(*unit)->getIsEmpty()) {
					(*unit)->UnitWork();
				}
				if ((*unit)->getIsEmpty()) {//release here
					(*unit)->UnitRelease();
					if (std::next(unit) == subUnitGroup.end()) {
						subUnitGroup.erase(unit);
						if(subUnitGroup.empty())
							taskFinish = true;
						break;
					}
					else {
						unit = subUnitGroup.erase(unit);
						iterEnd = subUnitGroup.end();
					}
				}
			}
			taskNowDurationFrame++;
		}
		taskAccumlateTime++;
	}
	else {
		taskFinish = true;
	}
}

void Task::TaskWork()
{
	if (taskIsInit) {
		if (targetUUID.empty()) {
			taskSubWork();
		}
		else {
			if (TaskDispatcher::getTaskFinish(targetUUID)) {
				taskSubWork();
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

std::string Task::getTaskUUID()
{
	return taskUUID;
}
