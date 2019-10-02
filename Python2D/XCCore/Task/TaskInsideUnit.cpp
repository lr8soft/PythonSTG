#include "TaskInsideUnit.h"

TaskInsideUnit::TaskInsideUnit(int wFrame, int wInterval, int rTime): waitFrame(wFrame), workInterval(wInterval), repeatTime(rTime)
{
	;
}

void TaskInsideUnit::UnitInit()
{
}

void TaskInsideUnit::UnitWork()
{
	if (waitFrame > 0) {
		waitFrame--;
	}
	else {
		for (auto bullet:bulletGroup) {
			bullet->BulletRender();
		}
	}
}

void TaskInsideUnit::UnitRelease()
{
	auto iterBegin = bulletGroup.begin();
	auto iterEnd = bulletGroup.end();
	for (auto iter = iterBegin; iter != iterEnd; iter++) {
		delete *iter;
	}
	bulletGroup.clear();
}

void TaskInsideUnit::addBullet(Bullet * pBullet)
{
	bulletGroup.push_back(pBullet);
}
