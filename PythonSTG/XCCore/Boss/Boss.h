#pragma once
#ifndef _BOSS_H_
#define _BOSS_H_
#include "../Task/Task.h"
#include "BossObject.h"
#include "SpellCard.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Boss :public Task{
protected:
	bool haveSpellCardAddToQueue = false, haveAddRenderObjectToQueue = false;
	bool isNewSpellCard = true;
	std::vector<SpellCard*> spellCardGroup;
	std::string bossName, currentUuid;
	BossObject* bossRenderObject;

	std::string imagePath;
	glm::vec2 divideInfo;
	glm::vec2 scaleInfo;
	int standByRow;
	int walkRow;
	int attackRow;

	virtual void taskSubWork() override;
public:
	Boss(std::string uuid, std::vector<std::string>& targetUUID ,std::string bossName, int waitFrame,
		std::string imagePath, glm::vec2 divideInfo, glm::vec2 scaleInfo,int standByRow, int walkRow, int attackRow);

	void AddSpellCard(SpellCard* spellcard);

	virtual void TaskInit() override;
	virtual void TaskRelease() override;

};
#endif