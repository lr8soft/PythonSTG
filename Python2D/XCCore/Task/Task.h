#pragma once
#ifndef _TASK_H_
#define _TASK_H_
#include <string>
#include <vector>
#include "TaskInsideUnit.h"
class Task {
protected:
	std::string taskUUID, targetUUID;
	int taskDurationFrame = -1, taskIntervalFrame = 0;
	int taskNowDurationFrame = 0, taskAccumlateTime = 0;
	bool taskFinish = false, taskIsInit = false;

	std::vector<TaskInsideUnit*> subUnitGroup;

	void taskSubWork();
public:
	/*while taskType==TaskWait, the task will wait for target task to end and start.
	repeatTime == -1 means task will work repeatedly.*/
	Task(std::string taskUuid, std::string targetTaskUuid, int repeatTime, int intervalFrame);
	void addSubUnit(TaskInsideUnit* unit);

	virtual void TaskInit();
	virtual void TaskWork();
	virtual void TaskRelease();

	bool getTaskFinish();
	bool getTaskInit();
	std::string getTaskUUID();
};
#endif