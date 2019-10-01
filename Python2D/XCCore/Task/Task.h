#pragma once
#ifndef _TASK_H_
#define _TASK_H_
#include <string>
class Task {
protected:
	std::string taskUUID, targetUUID;
	int taskType = TaskDetach;
	int taskRepeatTime = -1, taskIntervalFrame = 0;
	bool taskFinish = false, taskIsInit = false;
public:
	static enum TaskType {
		TaskDetach = 0, TaskWait
	};

	/*while taskType==TaskWait, the task will wait for target task to end and start.
	repeatTime == -1 means task will work repeatedly.*/
	Task(std::string taskUuid, TaskType type, std::string targetTaskUuid, int repeatTime = -1, int intervalFrame = 0);

	void TaskInit();
	void TaskWork();
	void TaskRelease();	

	bool getTaskFinish();
	std::string getTaskUUID();
};
#endif