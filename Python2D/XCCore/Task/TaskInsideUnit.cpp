#include "TaskInsideUnit.h"
#include "../XCCollide/CollideInfo.h"
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
		auto iterBegin = bulletGroup.begin();
		auto iterEnd = bulletGroup.end();
		for (auto bullet = iterBegin; bullet != iterEnd;bullet++) {
			if (!(*bullet)->getIsTerminate()) {
				(*bullet)->BulletRender();

				auto collideHelperP1 = CollideInfo::getCollideHelperP1();
				if (collideHelperP1 != nullptr) {
					collideHelperP1->checkCollisionWithBullet((*bullet));
				}
			}

			if ((*bullet)->getIsTerminate()) {
				(*bullet)->BulletRelease();
				delete *bullet;
				if (std::next(bullet) == bulletGroup.end()) {
					bulletGroup.erase(bullet);
					return;
				}
				else {
					bullet = bulletGroup.erase(bullet);
					iterEnd = bulletGroup.end();
				}
			}
		}
	}
}

void TaskInsideUnit::UnitRelease()
{
	auto iterBegin = bulletGroup.begin();
	auto iterEnd = bulletGroup.end();
	if (!bulletGroup.empty()) {
		for (auto iter = iterBegin; iter != iterEnd; iter++) {
			(*iter)->BulletRelease();
			delete *iter;
		}
	}
	bulletGroup.clear();
}

void TaskInsideUnit::addBullet(Bullet * pBullet)
{
	bulletGroup.push_back(pBullet);
}

bool TaskInsideUnit::getIsEmpty()
{
	return bulletGroup.empty();
}
