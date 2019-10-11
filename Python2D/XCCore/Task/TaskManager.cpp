#include <iostream>
#include <chrono>
#include <future>
#include <GL3/gl3w.h>
#include <GLFW/glfw3.h>

#include "TaskManager.h"
#include "../../XCFrameInfo.h"
#include "../UserInterface/GameInfoInterface.h"
#include "../UserInterface/CoverInterface.h"
#include "../XCCollide/CollideInfo.h"
TaskManager* TaskManager::pRManager = nullptr;
TaskManager::TaskManager()
{
	auto coverInterface = CoverInterface::getInstance();
	AddUserInterface("coverImage", coverInterface);

	auto infoInterface = GameInfoInterface::getInstance();
	AddUserInterface("gameInfo", infoInterface);
}

TaskManager * TaskManager::getInstance()
{
	if (pRManager==nullptr) {
		pRManager = new TaskManager;
	}
	if (pRManager->getPlayerP1() == nullptr)
	{
		auto group = Player::getPlayerGroup();
		if (!group->empty()) {
			pRManager->setPlayerP1(group->begin()->second);
		}
	}
	return pRManager;
}


void TaskManager::AddStageItem(Stage * stage)
{
	stageQueue.push_back(stage);
}
void TaskManager::AddUserInterface(std::string uiName, IUserInterface * ui)
{
	uiGroup.insert(std::make_pair(uiName, ui));
}
void TaskManager::TaskWork()
{
	if (!shouldGamePause) {
		glClear(GL_COLOR_BUFFER_BIT);
		if (renderBackground != nullptr) {
			renderBackground->BackgroundRender();
		}
		if (playerP1 != nullptr) {
			if (!playerP1->getIsInit()) {
				playerP1->PlayerInit();
			}
			if (playerP1->getIsInit()) {
				playerP1->PlayerRender();
			}

		}
		std::vector<Stage*>::iterator stageBegin = stageQueue.begin();
		std::vector<Stage*>::iterator stageEnd = stageQueue.end();
		if (stageBegin != stageEnd) {//only one stage will work
			Stage* stageItem = (*stageBegin);
			if (!stageItem->getStageInit()) {
				stageItem->stageInit();
			}
			if (stageItem->getStageFinish()) {
				stageQueue.erase(stageBegin);
				renderBackground = nullptr;
				delete stageItem;
				return;
			}
			if (stageItem->getStageInit()) {
				stageItem->stageWork();
				renderBackground = stageItem->getBackgroundPointer();
			}
		}
	}

	std::map<std::string, IUserInterface*>::iterator uiBegin = uiGroup.begin();
	std::map<std::string, IUserInterface*>::iterator uiEnd = uiGroup.end();
	for (auto uiIter = uiBegin; uiIter != uiEnd; uiIter++) {
		IUserInterface* ui = uiIter->second;

		if (!ui->getIsInit()) {
			ui->UserInterfaceInit();
		}
		if (ui->getIsInit()) {
			ui->UserInterfaceRender();
			shouldGamePause = ui->getShouldPauseGame();
		}
		if (ui->getIsWorkFinish()) {
			if (std::next(uiIter) == uiEnd)
			{
				uiGroup.erase(uiIter);
				break;
			}
			else {
				uiGroup.erase(uiIter++);
				uiEnd = uiGroup.end();
			}
		}

	}
}

Player * TaskManager::getPlayerP1()
{
	return playerP1;
}

void TaskManager::setPlayerP1(Player * p1)
{
	playerP1 = p1;
	CollideInfo::setCollideHelperP1(new CollideHelper(p1));
}
