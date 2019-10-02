#pragma once
#ifndef _TASK_DISPATCHER_H_
#define _TASK_DISPATCHER_H_
#include <map>
#include <mutex>
#include <string>
class TaskDispatcher {
private:
	static std::mutex taskMutex;
	static std::map<std::string, bool> StageTaskGroup;
public:
	static void addTask(std::string uuid);
	static void updateTask(std::string uuid, bool isFinsh);
	static bool getTaskFinish(std::string targetUuid);
	static void clearTask();
};
#endif