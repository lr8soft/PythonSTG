#include "RenderManager.h"

std::vector<RenderItem> RenderManager::renderQueue;
RenderManager* RenderManager::pRManager = nullptr;
RenderManager * RenderManager::getInstance()
{
	if (pRManager==nullptr) {
		pRManager = new RenderManager;
	}
	return pRManager;
}

void RenderManager::AddWork(RenderItem work)
{
	renderQueue.push_back(work);
}

void RenderManager::RenderWork()
{
	std::vector<RenderItem>::iterator workBegin = renderQueue.begin();
	std::vector<RenderItem>::iterator workEnd = renderQueue.end();
	for (auto work = workBegin; work != workEnd; work++) {
		if (work->visible && work->image!=nullptr) {
			work->image->ImageRender(
				work->renderPos,
				work->renderColor, 
				work->scaleSize,
				work->image->GetSpecificTexture(work->divideInfo[0], work->divideInfo[1], work->divideInfo[2], work->divideInfo[3])
			);
		}
	}
}
