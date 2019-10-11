#include "RenderManager.h"
#include "../Bullet/Bullet.h"
#include "../XCCollide/CollideInfo.h"
RenderManager* RenderManager::pRenderManager = nullptr;
RenderManager::RenderManager() {
	;
}
RenderManager * RenderManager::getInstance()
{
	if (pRenderManager == nullptr) {
		pRenderManager = new RenderManager;
	}
	return pRenderManager;
}

void RenderManager::AddRenderObject(RenderObject * object)
{
	renderObjectList.push_back(object);
	object->Init();
}

void RenderManager::RenderWork()
{
	std::vector<RenderObject*>::iterator renderBegin = renderObjectList.begin();
	std::vector<RenderObject*>::iterator renderEnd = renderObjectList.end();
	for (auto object = renderBegin; object != renderEnd; object++) {
		RenderObject *renderObject = (*object);
		if (!renderObject->getIsTerminate()) {
			renderObject->Render();

			Bullet* pBullet = dynamic_cast<Bullet*>(renderObject);
			if (pBullet != nullptr) {
				auto collideHelperP1 = CollideInfo::getCollideHelperP1();
				if (collideHelperP1 != nullptr) {
					collideHelperP1->checkCollisionWithBullet(pBullet);
				}
			}
		}
		if (renderObject->getIsTerminate()) {
			renderObject->Release();
			delete renderObject;
			if (std::next(object) == renderEnd)
			{
				renderObjectList.erase(object);
				break;
			}
			else {
				object = renderObjectList.erase(object);
				renderEnd = renderObjectList.end();
			}
		}
	}
}

void RenderManager::CleanRenderObject()
{
	std::vector<RenderObject*>::iterator renderBegin = renderObjectList.begin();
	std::vector<RenderObject*>::iterator renderEnd = renderObjectList.end();
	for (auto object = renderBegin; object != renderEnd; object++) {
		RenderObject *renderObject = (*object);
		renderObject->Release();
		delete renderObject;
		if (std::next(object) == renderEnd)
		{
			renderObjectList.erase(object);
			break;
		}
		else {
			object = renderObjectList.erase(object);
			renderEnd = renderObjectList.end();
		}
	}
}

bool RenderManager::CheckRenderComplete()
{
	return renderObjectList.empty();
}
