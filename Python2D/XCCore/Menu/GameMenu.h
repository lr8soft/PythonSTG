#pragma once
#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_
#include <map>
#include "IMenu.h"
#include "../../util/GameTimer.h"
#include "../XCAudio/AudioHelper.h"
#include "../XCRender/XCFont.h"
#include "../XCRender/XCImageHelper.h"
class GameMenu :public IMenu{
private:
	std::map<int, std::string> menuItem;
	XCFont fontHelper;
	XCGameTimer timer;

	XCWavFile confirmEffect, cancelEffect;
	int nowSelectIndex = 0;
	long double lastClickTime = 0.0;
	
	void checkKeyInput();
public:
	GameMenu();
	virtual void Init() override;
	virtual void Render() override;
	virtual void Release() override;
};
#endif