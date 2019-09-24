#include "RenderManager.h"
#include "XCImageHelper.h"
#include "XCColorBlockHelper.h"
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
			if (std::string("image")._Equal(work->renderType)) {
				work->image = new XCImageHelper(work->imagePath, work->flexible);
			}else if (std::string("colorblock")._Equal(work->renderType)) {
				work->image = new XCColorBlockHelper;
			}
			work->init = true;
		}
		if (work->init && work->visible) {
			work->image->Render(
				work->renderPos,
				work->renderColor, 
				work->scaleSize,
				XCImageHelper::GetSpecificTexture(work->divideInfo[0], work->divideInfo[1], work->divideInfo[2], work->divideInfo[3])
			);
		}
	}
	renderMutex.unlock();
}
