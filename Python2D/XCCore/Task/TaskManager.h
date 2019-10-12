#pragma once
#ifndef _TaskManager_H_
#define _TaskManager_H_
#include <vector>
#include <string>

#include "../Stage/Stage.h"
class TaskManager {
private:
	std::vector<Stage*> stageQueue;

	static TaskManager* pRManager;
	TaskManager();
public:
	static TaskManager* getInstance();
	void AddStageItem(Stage* stage);
	void TaskWork();
};
#endif