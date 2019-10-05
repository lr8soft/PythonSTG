#include <chrono>
#include <future>
#include "RenderManager.h"
#include "XCImageHelper.h"
#include "XCColorBlockHelper.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../XCFrameInfo.h"
RenderManager* RenderManager::pRManager = nullptr;
RenderManager::RenderManager()
{
}

RenderManager * RenderManager::getInstance()
{
	if (pRManager==nullptr) {
		pRManager = new RenderManager;
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

void RenderManager::AddStaticWork(StaticRenderItem work)
{
	staticQueue.push_back(work);
}
void RenderManager::AddStageItem(Stage * stage)
{
	stageQueue.push_back(stage);
}
void RenderManager::RenderWork()
{
	std::vector<StaticRenderItem>::iterator workBegin = staticQueue.begin();
	std::vector<StaticRenderItem>::iterator workEnd = staticQueue.end();

	for (auto work = workBegin; work != workEnd; work++) {//static render work
		if (!work->init) {
			if ("image" == work->renderType) {
				work->image = new XCImageHelper(work->imagePath, work->flexible);
			}
			else if ("colorblock" == work->renderType) {
				work->image = new XCColorBlockHelper(work->flexible);
			}
			work->init = true;
		}
		if (work->init && work->visible) {
			work->image->Render(
				work->renderPos,
				work->renderColor,
				0.0f,
				glm::vec3(1),
				work->scaleSize,
				IRenderHelper::GetSpecificTexWithRate(
					XCFrameInfo::FrameRight, XCFrameInfo::FrameTop,
					work->divideInfo[0], work->divideInfo[1], work->divideInfo[2], work->divideInfo[3])
			);
		}
	}
	if (renderBackground != nullptr) {
		renderBackground->BackgroundRender();
	}
	if (playerP1 != nullptr) {
		if (!playerP1->getIsInit()) {
			playerP1->ItemInit();
		}
		if (playerP1->getIsInit()) {
			playerP1->ItemRender();
		}

	}
	std::vector<Stage*>::iterator stageBegin = stageQueue.begin();
	std::vector<Stage*>::iterator stageEnd = stageQueue.end();
	if (stageBegin != stageEnd) {
		Stage* stageItem = (*stageBegin);
		if (!stageItem->getStageInit()) {
			stageItem->stageInit();
			renderBackground = stageItem->getBackgroundPointer();
		}
		if (stageItem->getStageFinish()) {
			stageQueue.erase(stageBegin);
			renderBackground = nullptr;
			delete stageItem;
			return;
		}
		if (stageItem->getStageInit()) {
			stageItem->stageWork();
		}
	}

}

Player * RenderManager::getPlayerP1()
{
	return playerP1;
}

void RenderManager::setPlayerP1(Player * p1)
{
	playerP1 = p1;
}
