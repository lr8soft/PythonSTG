#pragma once
#ifndef _TaskManager_H_
#define _TaskManager_H_
#include <vector>
#include <string>
#include <mutex>
#include <map>

#include "../UserInterface/IUserInterface.h"
#include "../Stage/Stage.h"
#include "../Item/Player.h"
#include "../Background/Background.h"
class TaskManager {
private:
	std::vector<Stage*> stageQueue;
	std::map<std::string, IUserInterface*> uiGroup;

	bool shouldGamePause = false;
	Background *renderBackground = nullptr;
	Player* playerP1;

	static TaskManager* pRManager;
	TaskManager();
public:
	static TaskManager* getInstance();

	void AddStageItem(Stage* stage);
	void AddUserInterface(std::string uiName, IUserInterface* ui);

	void TaskWork();

	Player* getPlayerP1();
	void setPlayerP1(Player* p1);
};
#endif