#include "TaskInsideUnit.h"
#include "../XCRender/RenderManager.h"
TaskInsideUnit::TaskInsideUnit(std::string uuid, int wFrame, int rTime): parentUuid(uuid),waitFrame(wFrame), repeatTime(rTime)
{
	nowFrame = wFrame;
}

void TaskInsideUnit::UnitInit()
{
}

void TaskInsideUnit::UnitWork()
{
	if (nowFrame > 0) {
		nowFrame--;
	}
	else {
		if (repeatTime > 0) {
			if (!haveAddToQueue) {
				auto iterBegin = renderObjectGroup.begin();
				auto iterEnd = renderObjectGroup.end();
				for (auto object = iterBegin; object != iterEnd; object++) {
					RenderManager::getInstance()->AddRenderObject(parentUuid, *object);
				}
				renderObjectGroup.clear();

				/*Refill render object*/
				auto groupBegin = renderGroupManager.begin();
				if (groupBegin != renderGroupManager.end()) {
					std::list<RenderObject*> list = *groupBegin;
					renderObjectGroup.assign(list.begin(), list.end());
					renderGroupManager.erase(groupBegin);
				}
				else {
					haveAddToQueue = true;
				}

				repeatTime--;
				nowFrame = waitFrame;
			}
		}
		else {
			haveAddToQueue = true;
		}

	}
}

void TaskInsideUnit::UnitRelease()
{
	if (!renderObjectGroup.empty()) {
		for (auto object = renderObjectGroup.begin(); object != renderObjectGroup.end(); object++) {
			(*object)->Release();
			delete *object;
		}	
		renderObjectGroup.clear();
	}

	if (!renderGroupManager.empty()) {
		auto iterBegin = renderGroupManager.begin();
		auto iterEnd = renderGroupManager.end();
		for (auto object = iterBegin; object != iterEnd; object++) {
			for (auto robject = object->begin(); robject != object->end(); robject++) {
				(*robject)->Release();
				delete *robject;
			}
			object->clear();
		}
		renderGroupManager.clear();
	}
}

void TaskInsideUnit::addRenderObject(RenderObject * pObject)
{
	renderObjectGroup.push_back(pObject);
}

void TaskInsideUnit::addRenderGroup(std::list<RenderObject*> group)
{
	renderGroupManager.push_back(group);
}

void TaskInsideUnit::setBulletInitCoord(float x, float y, float z)
{
	auto iterBegin = renderObjectGroup.begin();
	auto iterEnd = renderObjectGroup.end();
	for (auto object = iterBegin; object != iterEnd; object++) {
		RenderObject* renderObject = *object;
		if (renderObject->getCurrentType() == RenderObject::BulletType) {
			Bullet* bullet = static_cast<Bullet*>(renderObject);
			bullet->setPosition(x, y, z);
		}
	}
}

bool TaskInsideUnit::IsAddToQueue()
{
	return haveAddToQueue;
}
