#include "Task.h"


Task::Task(std::string taskUuid, TaskType type, std::string uuidForWaitTask, int repeatTime, int intervalFrame)
{
	taskUUID = taskUuid;
	taskType = type;
	targetUUID = uuidForWaitTask;

	taskRepeatTime = repeatTime;
	taskIntervalFrame = intervalFrame;
}

void Task::TaskInit()
{
	if (!taskIsInit) {
	
		taskIsInit = true;
	}
}

void Task::TaskWork()
{
}

void Task::TaskRelease()
{
}

bool Task::getTaskFinish()
{
	return taskFinish;
}

std::string Task::getTaskUUID()
{
	return taskUUID;
}
