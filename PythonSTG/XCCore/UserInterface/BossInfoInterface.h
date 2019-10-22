#pragma once
#ifndef _BOSS_INFO_INTERFACE_H_
#define _BOSS_INFO_INTERFACE_H_
#include "IUserInterface.h"
#define BossInfoInterfaceUuid "bossInfoInterfaceUUID"
class BossInfoInterface :public IUserInterface {
protected:
	static BossInfoInterface* pInstance;
	BossInfoInterface();
public:
	static BossInfoInterface* getInstance();
	virtual void UserInterfaceInit() override;
	virtual void UserInterfaceRender() override;
	virtual void UserInterfaceRelease() override;
};
#endif