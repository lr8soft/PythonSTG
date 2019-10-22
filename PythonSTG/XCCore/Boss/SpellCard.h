#pragma once
#ifndef _SPELL_CARD_H_
#define _SPELL_CARD_H_
#include <vector>
#include <string>
#include "../Task/Task.h"

class SpellCard {
protected:
	std::vector<Task*> taskGroup;
	std::vector<std::string> taskUUIDGroup;

	bool isSpellCard = true, isAddToQueue = false, isInit =false, isSpellCardFinish = false;
	std::string uuid, spellCardName;
	float spellCardTime = 0.0f, spellCardHitPoint;
public:
	SpellCard(std::string parentUuid, std::string spellCardName, bool isSpellCard, float spellCardTime, float spellCardHitPoint);
	void AddSpellCardTask(Task *pTask);

	void SpellCardInit();
	void SpellCardWork();
	void SpellCardRelease();

	bool haveAddToQueue();
	bool getIsFinish();
};
#endif