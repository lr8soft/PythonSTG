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

void RenderManager::AddRenderObject(std::string parentUuid, RenderObject * object)
{
	renderObjectList.insert(std::make_pair(parentUuid, object));
	object->Init();
}

void RenderManager::RenderWork()
{
	std::multimap<std::string, RenderObject*>::iterator renderBegin = renderObjectList.begin();
	std::multimap<std::string, RenderObject*>::iterator renderEnd = renderObjectList.end();
	for (auto object = renderBegin; object != renderEnd; object++) {
		RenderObject *renderObject = object->second;
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

void RenderManager::CleanRenderObject(std::string uuid)
{
	std::multimap<std::string, RenderObject*>::iterator renderBegin = renderObjectList.find(uuid);
	std::multimap<std::string, RenderObject*>::iterator renderEnd = renderObjectList.end();
	for (auto object = renderBegin; object != renderEnd; object = renderObjectList.find(uuid)) {
		RenderObject *renderObject = object->second;
		renderObject->Release();
		delete renderObject;
		if (std::next(object) == renderEnd)
		{
			renderObjectList.erase(object);
			break;
		}
		else {
			renderObjectList.erase(object++);
			renderEnd = renderObjectList.end();
		}
	}
}

bool RenderManager::CheckRenderComplete(std::string uuid)
{
	return  renderObjectList.find(uuid)== renderObjectList.end();
}
