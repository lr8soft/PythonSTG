#pragma once
#ifndef _BOSS_INFO_INTERFACE_H_
#define _BOSS_INFO_INTERFACE_H_
#include <string>
#include "../XCRender/XCFont.h"
#include "IUserInterface.h"
#define BossInfoInterfaceUuid "gameBossHP"
#include "../XCRender/XCAdvImageHelper.h"
class BossInfoInterface :public IUserInterface {
protected:
	XCFont fontHelper;
	XCAdvImageHelper *spellCardStar, *spellcardBackground, *bossHitPoint;
	int spellCardCount = 3, spellCardTime = 0;
	std::string spellCardName = "TSC", bossName = "TBOSS";

	float nowBossHitPoint = 5.0f, maxBossHitPoint = 10.0f;
	BossInfoInterface();

	static BossInfoInterface* pInstance;
public:
	static BossInfoInterface* getInstance();
	virtual void UserInterfaceInit() override;
	virtual void UserInterfaceRender() override;
	virtual void UserInterfaceRelease() override;

	void setSpellCardCount(int count);
	void setSpellCardName(std::string name);
	void setSpellCardTime(int time);
	void setBossHitPoint(float currentHP, float maxHP);
	void setBossName(std::string name);
};
#endif