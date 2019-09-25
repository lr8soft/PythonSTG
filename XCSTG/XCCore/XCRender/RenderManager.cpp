#include <chrono>
#include <future>
#include "RenderManager.h"
#include "XCImageHelper.h"
#include "XCColorBlockHelper.h"
#include <GLFW/glfw3.h>
#include <iostream>
std::mutex RenderManager::staticMutex, RenderManager::dynamicMutex;
std::vector<StaticRenderItem> RenderManager::staticQueue;
std::vector<DynamicRenderItem> RenderManager::dynamicRenderGroup;
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

void RenderManager::AddDynamicWork(DynamicRenderItem work)
{
	dynamicMutex.lock();
	dynamicRenderGroup.push_back(work);
	dynamicMutex.unlock();
}

void RenderManager::AddStaticWork(StaticRenderItem work)
{
	staticMutex.lock();
	staticQueue.push_back(work);
	staticMutex.unlock();
}
void RenderManager::RenderWork()
{
	staticMutex.lock();
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
				work->scaleSize,
				XCImageHelper::GetSpecificTexture(work->divideInfo[0], work->divideInfo[1], work->divideInfo[2], work->divideInfo[3])
			);
		}
	}
	staticMutex.unlock();


	dynamicMutex.lock();
	std::vector<DynamicRenderItem>::iterator dyBegin = dynamicRenderGroup.begin();
	std::vector<DynamicRenderItem>::iterator dyEnd = dynamicRenderGroup.end();
	for (auto work = dyBegin; work != dyEnd; work++) {
		auto pItem = work->item;
		if (!pItem->getIsInit()) {
			pItem->ItemInit();//need gl environmenet
		}
		if (pItem->getIsInit()) {
			pItem->ItemRender();
		}
	}
	dynamicMutex.unlock();


}
