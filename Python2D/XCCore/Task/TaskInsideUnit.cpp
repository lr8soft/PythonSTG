#include "TaskInsideUnit.h"
#include "../XCRender/RenderManager.h"
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
		if (!haveAddToQueue) {
			auto iterBegin = bulletGroup.begin();
			auto iterEnd = bulletGroup.end();
			for (auto bullet = iterBegin; bullet != iterEnd; bullet++) {
				RenderManager::getInstance()->AddRenderObject(*bullet);
				/*if (!(*bullet)->getIsTerminate()) {
					(*bullet)->Render();

					auto collideHelperP1 = CollideInfo::getCollideHelperP1();
					if (collideHelperP1 != nullptr) {
						collideHelperP1->checkCollisionWithBullet((*bullet));
					}
				}

				if ((*bullet)->getIsTerminate()) {
					(*bullet)->Release();
					delete *bullet;
					if (std::next(bullet) == bulletGroup.end()) {
						bulletGroup.erase(bullet);
						return;
					}
					else {
						bullet = bulletGroup.erase(bullet);
						iterEnd = bulletGroup.end();
					}
				}*/
			}
			haveAddToQueue = true;
		}
		else {
			if (RenderManager::getInstance()->CheckRenderComplete()) {
				isFinish = true;
			}

		}
	}
}

void TaskInsideUnit::UnitRelease()
{
	//auto iterBegin = bulletGroup.begin();
	//auto iterEnd = bulletGroup.end();
	//if (!bulletGroup.empty()) {
	//	for (auto iter = iterBegin; iter != iterEnd; iter++) {
	//		(*iter)->Release();
	//		delete *iter;
	//	}
	//}
	bulletGroup.clear();
}

void TaskInsideUnit::addBullet(Bullet * pBullet)
{
	bulletGroup.push_back(pBullet);
}

bool TaskInsideUnit::getIsFinish()
{
	return isFinish;
}
