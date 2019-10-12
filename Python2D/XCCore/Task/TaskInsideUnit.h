#pragma once
#ifndef _TASKINSIDE_UNIT_H_
#define _TASKINSIDE_UNIT_H_
#include "../Item/Item.h"
#include "../Bullet/Bullet.h"
#include <list>
#include <string>
class TaskInsideUnit {
private:
	int waitFrame, workInterval = 0, repeatTime = 0;
	bool haveAddToQueue = false, isFinish = false;
	std::list<Bullet*> bulletGroup;

	std::string parentUuid;
public:
	TaskInsideUnit(std::string uuid,int waitFrame, int workInterval, int repeatTime);

	void UnitInit();
	void UnitWork();
	void UnitRelease();

	void addBullet(Bullet* pBullet);
	bool getIsFinish();
};
#endif