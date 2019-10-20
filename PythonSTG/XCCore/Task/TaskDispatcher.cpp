#include "TaskDispatcher.h"
std::map<std::string, bool> TaskDispatcher::StageTaskGroup;
void TaskDispatcher::addTask(const std::string& uuid)
{
	StageTaskGroup.insert(std::make_pair(uuid, false));
}

void TaskDispatcher::updateTask(const std::string& uuid, bool isFinsh)
{
	std::map<std::string, bool>::iterator target = StageTaskGroup.find(uuid);
	if (target != StageTaskGroup.end()) {
		target->second = isFinsh;
	}
}

bool TaskDispatcher::getTaskFinish(const std::string& targetUuid)
{
	bool isTargetFinish = false;
	std::map<std::string, bool>::iterator target = StageTaskGroup.find(targetUuid);
	if (target != StageTaskGroup.end()) {
		isTargetFinish = target->second;
	}
	return isTargetFinish;
}

void TaskDispatcher::clearTask()
{
	StageTaskGroup.clear();
}
