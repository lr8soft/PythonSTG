#pragma once
#ifndef _SPELL_CARD_H_
#define _SPELL_CARD_H_
#include <vector>
#include <string>
#include "../Task/Task.h"
#include "../Item/ItemHelper.h"
#include "../../util/GameTimer.h"
#include "../Boss/BossObject.h"
#include <glm/glm.hpp>
class SpellCard {
protected:
	XCGameTimer timer;
	std::vector<Task*> taskGroup;
	std::vector<std::string> taskUUIDGroup;


	bool isSpellCard = true, isAddToQueue = false, isInit =false, isSpellCardFinish = false;
	bool haveTaskCoordInit = false;
	std::string uuid, spellCardName;
	float spellCardTime = 0.0f, spellCardHitPoint;

	BossObject* pBossObject = nullptr;

	glm::vec2 movementPosition = glm::vec2(-2.0f, -2.0f);

	std::vector<DropItem>* dropItemList = nullptr;
public:
	SpellCard(std::string parentUuid, std::string spellCardName, bool isSpellCard, float spellCardTime, float spellCardHitPoint);
	void AddSpellCardTask(Task *pTask);

	void SpellCardInit();
	void SpellCardWork();
	void SpellCardRelease();

	void setMovementPosition(float x, float y);

	void setBossObject(BossObject* pObject);
	void setDropItem(std::vector<DropItem>* pItem);
	std::vector<DropItem>* getDropItem();

	float getSpellCardTime();
	float getSpellCardHitPoint();
	glm::vec2 getMovement();
	std::string getSpellCardName();

	bool haveAddToQueue();
	bool getIsFinish();
};
#endif