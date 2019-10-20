#pragma once
#ifndef _PAUSE_MENU_H_
#define _PAUSE_MENU_H_
#include <map>
#include "IMenu.h"
#include "../XCAudio/AudioHelper.h"
#include "../../util/GameTimer.h"
class PauseMenu :public IMenu {
private:
	XCGameTimer timer;

	XCWavFile confirmEffect, cancelEffect;
	int nowSelectIndex = 0;
	long double lastClickTime = 0.0;

	void checkKeyInput();
public:
	PauseMenu();
	virtual void Init() override;
	virtual void Render() override;
	virtual void Release() override;
};
#endif