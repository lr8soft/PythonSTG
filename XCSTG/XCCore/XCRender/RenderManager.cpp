#include <chrono>
#include <future>
#include "RenderManager.h"
#include "XCImageHelper.h"
#include "XCColorBlockHelper.h"
#include <GLFW/glfw3.h>
std::mutex RenderManager::staticMutex, RenderManager::dynamicMutex;
std::vector<StaticRenderItem> RenderManager::staticQueue;
std::map<std::string, DynamicRenderItem> RenderManager::dynamicRenderGroup;
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

void RenderManager::AddDynamicWork(std::string uuid, DynamicRenderItem work)
{
	dynamicMutex.lock();
	dynamicRenderGroup.insert(std::make_pair(uuid,work));
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
	dynamicMutex.lock();
	std::map<std::string, DynamicRenderItem>::iterator dyBegin = dynamicRenderGroup.begin();
	std::map<std::string, DynamicRenderItem>::iterator dyEnd = dynamicRenderGroup.end();
	for (auto work = dyBegin; work != dyEnd; work++) {

	}
	dynamicMutex.unlock();

	staticMutex.lock();
	std::vector<StaticRenderItem>::iterator workBegin = staticQueue.begin();
	std::vector<StaticRenderItem>::iterator workEnd = staticQueue.end();
	
	for (auto work = workBegin; work != workEnd; work++) {//static render work
		if (!work->init) {
			if ("image"==work->renderType) {
				work->image = new XCImageHelper(work->imagePath, work->flexible);
			}else if ("colorblock" == work->renderType) {
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
}
