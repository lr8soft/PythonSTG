#pragma once
#ifndef _TaskManager_H_
#define _TaskManager_H_
#include <vector>
#include <string>
#include "../Task/Task.h"
#include "../Stage/Stage.h"
class TaskManager {
private:
	std::vector<Stage*> stageQueue;
	std::vector<Task*> asyncTaskGroup;
	std::vector<std::string> asyncCleanGroup;

	static TaskManager* pRManager;
	TaskManager();
public:
	static TaskManager* getInstance();

	void AddTaskAsync(Task* pTask);
	void AddStageItem(Stage* stage);
	void CleanTaskAsync(std::string &uuid);

	void CleanAllStage();
	void TaskWork();
};
#endif