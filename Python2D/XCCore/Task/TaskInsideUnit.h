#pragma once
#ifndef _TASKINSIDE_UNIT_H_
#define _TASKINSIDE_UNIT_H_
#include "../Item/Item.h"
#include "../Bullet/Bullet.h"
#include <list>
class TaskInsideUnit {
private:
	int waitFrame, workInterval = 0, repeatTime = 0;

	std::list<Bullet*> bulletGroup;
public:
	TaskInsideUnit(int waitFrame, int workInterval, int repeatTime);

	void UnitInit();
	void UnitWork();
	void UnitRelease();

	void addBullet(Bullet* pBullet);
	bool getIsEmpty();
};
#endif