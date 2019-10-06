#pragma once
#ifndef _GAME_INFO_INTERFACE_H_
#define _GAME_INFO_INTERFACE_H_
#include "IUserInterface.h"
#include "../XCRender/XCAdvImageHelper.h"
#include "../XCFont/XCFont.h"
#include "../../util/GameTimer.h"
class GameInfoInterface :public IUserInterface{
protected:
	/*
	bool isInit = false, pauseGame = false, workFinish = false;
	*/
	int gameRank = 4;
	long nowScore = 0, highScore = LONG_MAX;

	XCAdvImageHelper *rankImage, *playerInfoImage1, *playerInfoImage2;
	static GameInfoInterface* pInterface;
	XCGameTimer infoTimer;

	XCFont fontHelper;
	GameInfoInterface();
public:
	static GameInfoInterface* getInstance();

	virtual void UserInterfaceInit();
	virtual void UserInterfaceRender();
	virtual void UserInterfaceRelease();

	/*1:easy 2:normal 3:hard 4:lunatic 5:extra*/
	void setRank(int rank);
	void setNowScore(long score);
	void setHightScore(long score);
};
#endif