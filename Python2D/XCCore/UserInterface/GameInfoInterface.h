#pragma once
#ifndef _GAME_INFO_INTERFACE_H_
#define _GAME_INFO_INTERFACE_H_
#include "IUserInterface.h"
#include "../XCRender/XCAdvImageHelper.h"
#include "../XCRender/XCFont.h"
class GameInfoInterface :public IUserInterface{
protected:
	/*
	bool isInit = false, pauseGame = false, workFinish = false;
	*/
	int gameRank = 4;
	long nowScore = 0, highScore = LONG_MAX;

	int nowLife = 2, maxLife = 8;
	int nowBomb = 2, maxBomb = 8;

	XCAdvImageHelper *rankImage, *playerInfoImage1, *playerInfoImage2;
	static GameInfoInterface* pInterface;

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

	void setNowBomb(int count);
	void setNowLife(int life);
};
#endif