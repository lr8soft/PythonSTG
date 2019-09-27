#include <chrono>
#include <future>
#include "RenderManager.h"
#include "XCImageHelper.h"
#include "XCColorBlockHelper.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../XCFrame.h"
RenderManager* RenderManager::pRManager = nullptr;
RenderManager::RenderManager()
{
}

RenderManager * RenderManager::getInstance()
{
	if (pRManager==nullptr) {
		pRManager = new RenderManager;
	}
	return pRManager;
}

void RenderManager::AddStaticWork(StaticRenderItem work)
{
	staticQueue.push_back(work);
}
void RenderManager::AddStageItem(XCStage * stage)
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
				work->image = new XCColorBlockHelper;
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
					XCFrame::FrameRight, XCFrame::FrameTop,
					work->divideInfo[0], work->divideInfo[1], work->divideInfo[2], work->divideInfo[3])
			);
		}
	}

	std::vector<XCStage*>::iterator stageBegin = stageQueue.begin();
	std::vector<XCStage*>::iterator stageEnd = stageQueue.end();
	if (stageBegin != stageEnd) {
		XCStage* stageItem = (*stageBegin);
		if (!stageItem->getStageInit()) {
			stageItem->stageInit();
		}
		if (stageItem->getStageFinish()) {
			stageQueue.erase(stageBegin);
			delete stageItem;
			return;
		}
		if (stageItem->getStageInit()) {
			stageItem->stageWork();
		}
	}
}
