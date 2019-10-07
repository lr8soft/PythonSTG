#include <iostream>
#include <chrono>
#include <future>
#include <GL3/gl3w.h>
#include <GLFW/glfw3.h>

#include "RenderManager.h"
#include "../../XCFrameInfo.h"
#include "../UserInterface/GameInfoInterface.h"
#include "../XCCollide/CollideInfo.h"
RenderManager* RenderManager::pRManager = nullptr;
RenderManager::RenderManager()
{
	auto infoInterface = GameInfoInterface::getInstance();
	AddUserInterface("gameInfo", infoInterface);
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
void RenderManager::AddUserInterface(std::string uiName, IUserInterface * ui)
{
	uiGroup.insert(std::make_pair(uiName, ui));
}
void RenderManager::RenderWork()
{
	if (!shouldGamePause) {
		glClear(GL_COLOR_BUFFER_BIT);
		std::vector<StaticRenderItem>::iterator workBegin = staticQueue.begin();
		std::vector<StaticRenderItem>::iterator workEnd = staticQueue.end();

		for (auto work = workBegin; work != workEnd; work++) {//static render work
			if (!work->init) {
				work->image = IRenderHelper::getRenderObjectByType(work->renderType, work->imagePath, work->flexible);
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

Player * RenderManager::getPlayerP1()
{
	return playerP1;
}

void RenderManager::setPlayerP1(Player * p1)
{
	playerP1 = p1;
	CollideInfo::collideHelperP1 = new CollideHelper(p1);
}
