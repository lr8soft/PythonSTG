#include "TaskDispatcher.h"
std::mutex TaskDispatcher::taskMutex;
std::map<std::string, bool> TaskDispatcher::StageTaskGroup;
void TaskDispatcher::addTask(std::string uuid)
{
	taskMutex.lock();
	StageTaskGroup.insert(std::make_pair(uuid, false));
	taskMutex.unlock();
}

void TaskDispatcher::updateTask(std::string uuid, bool isFinsh)
{
	taskMutex.lock();
	std::map<std::string, bool>::iterator target = StageTaskGroup.find(uuid);
	if (target != StageTaskGroup.end()) {
		target->second = isFinsh;
	}
	taskMutex.unlock();
}

bool TaskDispatcher::getTaskFinish(std::string targetUuid)
{
	bool isTargetFinish = false;
	taskMutex.lock();
	std::map<std::string, bool>::iterator target = StageTaskGroup.find(targetUuid);
	if (target != StageTaskGroup.end()) {
		isTargetFinish = target->second;
	}
	taskMutex.unlock();
	return isTargetFinish;
}

void TaskDispatcher::clearTask()
{
	taskMutex.lock();
	StageTaskGroup.clear();
	taskMutex.unlock();
}
