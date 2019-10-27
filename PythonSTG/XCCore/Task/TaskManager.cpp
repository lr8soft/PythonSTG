#include <iostream>
#include "TaskManager.h"
#include "../../XCFrameInfo.h"
#include "../XCCollide/CollideInfo.h"
#include "../XCRender/RenderManager.h"
#include "../../LaunchHelper.h"
#include "../Menu/IMenu.h"
TaskManager* TaskManager::pRManager = nullptr;
TaskManager::TaskManager()
{
	;
}

TaskManager * TaskManager::getInstance()
{
	if (pRManager==nullptr) {
		pRManager = new TaskManager;
	}

	return pRManager;
}

void TaskManager::AddTaskAsync(Task * pTask)
{
	asyncTaskGroup.push_back(pTask);
}

void TaskManager::AddStageItem(Stage * stage)
{
	stageQueue.push_back(stage);
}

void TaskManager::CleanTaskAsync(std::string & uuid)
{
	asyncCleanGroup.push_back(uuid);
}

void TaskManager::SetTaskInitCoord(std::string & uuid, float x, float y)
{
	std::vector<Stage*>::iterator stageBegin = stageQueue.begin();
	std::vector<Stage*>::iterator stageEnd = stageQueue.end();
	
	if (stageBegin != stageEnd) {
		Stage* stageItem = (*stageBegin);
		stageItem->setTaskInitCoord(uuid, x, y);
	}
}

void TaskManager::CleanAllStage()
{
	std::vector<Stage*>::iterator stageBegin = stageQueue.begin();
	std::vector<Stage*>::iterator stageEnd = stageQueue.end();
	for (auto stage = stageBegin; stage != stageEnd; stage++) {
		(*stage)->stageRelease();
		delete *stage;
	}
	stageQueue.clear();
}

void TaskManager::TaskWork()
{
	std::vector<Stage*>::iterator stageBegin = stageQueue.begin();
	std::vector<Stage*>::iterator stageEnd = stageQueue.end();
	if (stageBegin != stageEnd) {//only one stage will work
		Stage* stageItem = (*stageBegin);
		if (!stageItem->getStageInit()) {
			stageItem->stageInit();
		}
	
		if (stageItem->getStageInit()) {
			stageItem->stageWork();
			RenderManager::getInstance()->SetBackgroundPointer(stageItem->getBackgroundPointer());
		}	
		if (stageItem->getStageFinish()) {
			RenderManager::getInstance()->SetBackgroundPointer(nullptr);
			stageQueue.erase(stageBegin);
			delete stageItem;
			return;
		}
	}
	if (!asyncTaskGroup.empty()) {
		std::vector<Stage*>::iterator currentStage = stageQueue.begin();
		auto asyncTaskEnd = asyncTaskGroup.end();
		for (auto task = asyncTaskGroup.begin(); task != asyncTaskEnd; task++) {
			(*currentStage)->addTask(*task);
		}
		asyncTaskGroup.clear();
	}
	if (!asyncCleanGroup.empty()) {
		std::vector<Stage*>::iterator currentStage = stageQueue.begin();
		std::vector<std::string>::iterator uuidEnd = asyncCleanGroup.begin();
		for (auto uuid = asyncCleanGroup.begin(); uuid != uuidEnd; uuid++) {
			(*currentStage)->removeTask(*uuid);
		}
		asyncCleanGroup.clear();
	}

	if (stageQueue.empty()) {
		if(RenderManager::getInstance()->CheckRenderComplete(MenuUniformUUID)){
			LaunchHelper::LoadGameMenu();
		}	
	}
}