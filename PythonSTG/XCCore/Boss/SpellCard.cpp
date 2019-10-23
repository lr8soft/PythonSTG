#include "SpellCard.h"
#include "../Task/TaskManager.h"
#include "../Task/TaskDispatcher.h"
#include "../XCRender/RenderManager.h"
SpellCard::SpellCard(std::string pUuid, std::string scName, bool isSC, float scTime, float scHP)
{
	uuid = pUuid;
	spellCardName = scName;
	isSpellCard = isSC;
	spellCardTime = scTime;
	spellCardHitPoint = scHP;
}

void SpellCard::AddSpellCardTask(Task *task)
{
	taskGroup.push_back(task);
}

void SpellCard::SpellCardInit()
{
	if (!isInit) {
		std::vector<Task*>::iterator taskBegin = taskGroup.begin();
		std::vector<Task*>::iterator taskEnd = taskGroup.end();
		for (auto task = taskBegin; task != taskEnd; task++) {
			(*task)->TaskInit();
		}	
		isInit = true;
	}

}

void SpellCard::SpellCardWork()
{
	if (isInit) {
		if (!isAddToQueue) {
			std::vector<Task*>::iterator taskBegin = taskGroup.begin();
			std::vector<Task*>::iterator taskEnd = taskGroup.end();
			for (auto task = taskBegin; task != taskEnd; task++) {
				taskUUIDGroup.push_back((*task)->getTaskUUID());
				TaskManager::getInstance()->AddTaskAsync(*task);
			}
			taskGroup.clear();
			isAddToQueue = true;			
		}
		else {
			bool isTargetTaskFinish = true;
			for (int i = 0; i < taskUUIDGroup.size(); i++) {
				bool isSubFinish = TaskDispatcher::getTaskFinish(taskUUIDGroup[i]);
				if (!isSubFinish) {
					isTargetTaskFinish = false;
				}
			}
			if (isTargetTaskFinish) {
				isSpellCardFinish = true;
			}
		}
	}

}

void SpellCard::SpellCardRelease()
{
	if (isInit) {
		if (!isAddToQueue) {
			std::vector<Task*>::iterator taskBegin = taskGroup.begin();
			std::vector<Task*>::iterator taskEnd = taskGroup.end();
			for (auto task = taskBegin; task != taskEnd; task++) {
				(*task)->TaskRelease();
				delete *task;
				if (std::next(task) == taskGroup.end()) {
					taskGroup.erase(task);
					break;
				}
				else {
					task = taskGroup.erase(task);
					taskEnd = taskGroup.end();
				}
			}
		}
		isInit = false;
	}
}

void SpellCard::setMovementPosition(float x, float y)
{
	movementPosition.x = x;
	movementPosition.y = y;
}

float SpellCard::getSpellCardTime()
{
	return spellCardTime;
}

float SpellCard::getSpellCardHitPoint()
{
	return spellCardHitPoint;
}

glm::vec2 SpellCard::getMovement()
{
	return movementPosition;
}

std::string SpellCard::getSpellCardName()
{
	return spellCardName;
}

bool SpellCard::haveAddToQueue()
{
	return isAddToQueue;
}

bool SpellCard::getIsFinish()
{
	return isSpellCardFinish;
}
