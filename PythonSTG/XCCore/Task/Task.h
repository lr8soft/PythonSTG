#pragma once
#ifndef _TASK_H_
#define _TASK_H_
#include <string>
#include <vector>
#include "TaskInsideUnit.h"
class Task {
protected:
	std::string taskUUID;
	int taskDurationFrame = -1, taskIntervalFrame = 0, taskWaitFrame = 0;
	int taskNowDurationFrame = 0, taskAccumlateTime = 0;
	bool taskFinish = false, taskIsInit = false;
	bool taskWait = false, taskWaitForTarget = false;

	std::vector<std::string> targetUUID;
	std::vector<TaskInsideUnit*> subUnitGroup;

	virtual void taskSubWork();
public:
	/*while taskType==TaskWait, the task will wait for target task to end and start.
	repeatTime == -1 means task will work repeatedly.*/
	Task(std::string taskUuid, std::vector<std::string> targetTaskUuid, int repeatTime, int intervalFrame, int waitFrame);
	void addSubUnit(TaskInsideUnit* unit);

	virtual void TaskInit();
	virtual void TaskWork();
	virtual void TaskRelease();

	bool getTaskFinish();
	bool getTaskInit();

	bool getIsTaskWaiting();
	bool getIsTaskWaitingForTarget();
	std::string getTaskUUID();
};
#endif