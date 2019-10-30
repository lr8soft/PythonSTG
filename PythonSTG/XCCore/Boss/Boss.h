#pragma once
#ifndef _BOSS_H_
#define _BOSS_H_
#include "../Task/Task.h"
#include "../XCAudio/AudioHelper.h"
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
	bool haveBossMusic = false;
	std::string bossName, currentUuid, bossMusicPath;
	BossObject* bossRenderObject;

	std::string imagePath;
	glm::vec2 divideInfo;
	glm::vec2 scaleInfo;
	int standByRow;
	int walkRow;
	int attackRow;

	ALuint bossMusic, stageMusic;

	virtual void taskSubWork() override;
public:
	Boss(std::string uuid, std::vector<std::string>& targetUUID ,std::string bossName, std::string bossMusic, int waitFrame,
		std::string imagePath, glm::vec2 divideInfo, glm::vec2 scaleInfo,int standByRow, int walkRow, int attackRow);

	void AddSpellCard(SpellCard* spellcard);

	virtual void TaskInit() override;
	virtual void TaskWork() override;
	virtual void TaskRelease() override;

};
#endif