#pragma once
#ifndef _TASK_DISPATCHER_H_
#define _TASK_DISPATCHER_H_
#include <map>
#include <string>
class TaskDispatcher {
private:
	static std::map<std::string, bool> StageTaskGroup;
public:
	static void addTask(const std::string& uuid);
	static void updateTask(const std::string& uuid, bool isFinsh);
	static bool getTaskFinish(const std::string& targetUuid);
	static void clearTask();
};
#endif