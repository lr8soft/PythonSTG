#include "RenderManager.h"
std::mutex RenderManager::renderMutex;
std::vector<RenderItem> RenderManager::renderQueue;
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

void RenderManager::AddWork(RenderItem work)
{
	renderMutex.lock();
	renderQueue.push_back(work);
	renderMutex.unlock();
}

void RenderManager::RenderWork()
{
	renderMutex.lock();
	std::vector<RenderItem>::iterator workBegin = renderQueue.begin();
	std::vector<RenderItem>::iterator workEnd = renderQueue.end();
	
	for (auto work = workBegin; work != workEnd; work++) {
		if (!work->init) {
			work->image = new XCImageManager(work->imagePath, work->flexible);
			work->init = true;
		}
		if (work->init && work->visible) {
			work->image->ImageRender(
				work->renderPos,
				work->renderColor, 
				work->scaleSize,
				work->image->GetSpecificTexture(work->divideInfo[0], work->divideInfo[1], work->divideInfo[2], work->divideInfo[3])
			);
		}
	}
	renderMutex.unlock();
}
