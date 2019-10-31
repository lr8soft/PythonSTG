#pragma once
#ifndef _TASKINSIDE_UNIT_H_
#define _TASKINSIDE_UNIT_H_
#include "../XCRender/RenderObject.h"
#include "../Bullet/Bullet.h"
#include <list>
#include <string>
class TaskInsideUnit {
protected:
	int waitFrame, repeatTime = 0, nowFrame = 0;
	bool haveAddToQueue = false, isFinish = false, isInit =false;
	std::list<RenderObject*> renderObjectGroup;
	std::list<std::list<RenderObject*>> renderGroupManager;

	std::string parentUuid;
public:
	TaskInsideUnit(std::string uuid,int waitFrame, int repeatTime);

	virtual void UnitInit();
	virtual void UnitWork();
	virtual void UnitRelease();

	virtual void addRenderObject(RenderObject* pObject);
	void addRenderGroup(std::list<RenderObject*> group);

	void setBulletInitCoord(float x, float y, float z);
	bool IsAddToQueue();
};
#endif