#pragma once
#ifndef _TASKINSIDE_UNIT_H_
#define _TASKINSIDE_UNIT_H_
#include "../Item/Item.h"
#include "../XCRender/RenderObject.h"
#include "../Bullet/Bullet.h"
#include <list>
#include <string>
class TaskInsideUnit {
private:
	int waitFrame, workInterval = 0, repeatTime = 0;
	bool haveAddToQueue = false, isFinish = false;
	std::list<RenderObject*> renderObjectGroup;

	std::string parentUuid;
public:
	TaskInsideUnit(std::string uuid,int waitFrame, int workInterval, int repeatTime);

	void UnitInit();
	void UnitWork();
	void UnitRelease();

	void addRenderObject(RenderObject* pObject);
	bool IsAddToQueue();
};
#endif