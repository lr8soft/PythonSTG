#include <iostream>
#include "TaskManager.h"
#include "../../XCFrameInfo.h"
#include "../XCCollide/CollideInfo.h"
#include "../XCRender/RenderManager.h"
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

void TaskManager::AddStageItem(Stage * stage)
{
	stageQueue.push_back(stage);
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
		if (stageItem->getStageFinish()) {
			RenderManager::getInstance()->SetBackgroundPointer(nullptr);
			stageQueue.erase(stageBegin);
			delete stageItem;
			return;
		}
		if (stageItem->getStageInit()) {
			stageItem->stageWork();
			RenderManager::getInstance()->SetBackgroundPointer(stageItem->getBackgroundPointer());
		}
	}
}