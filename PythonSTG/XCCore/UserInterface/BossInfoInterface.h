#pragma once
#ifndef _BOSS_INFO_INTERFACE_H_
#define _BOSS_INFO_INTERFACE_H_
#include <string>
#include "../XCRender/XCFont.h"
#include "IUserInterface.h"
#define BossInfoInterfaceUuid "bossInfoInterfaceUUID"
#include "../XCRender/XCAdvImageHelper.h"
class BossInfoInterface :public IUserInterface {
protected:
	XCFont fontHelper;
	XCAdvImageHelper *spellCardStar, *spellcardBackground;
	int spellCardCount = 3;
	std::string spellCardName = "TSC", bossName = "TBOSS";
	BossInfoInterface();

	static BossInfoInterface* pInstance;
public:
	static BossInfoInterface* getInstance();
	virtual void UserInterfaceInit() override;
	virtual void UserInterfaceRender() override;
	virtual void UserInterfaceRelease() override;

	void setSpellCardCount(int count);
	void setSpellCardName(std::string name);
	void setBossName(std::string name);
};
#endif