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

	static int nowLife , maxLife ;
	static int nowBomb , maxBomb ;

	XCAdvImageHelper *rankImage, *playerInfoImage1, *playerInfoImage2, *lifeBombImage;
	static GameInfoInterface* pInterface;

	XCFont fontHelper;
	GameInfoInterface();

	void renderPlayerLife(float x, float y);
	void renderPlayerBomb(float x, float y);
public:
	static GameInfoInterface* getInstance();

	virtual void UserInterfaceInit();
	virtual void UserInterfaceRender();
	virtual void UserInterfaceRelease();

	/*1:easy 2:normal 3:hard 4:lunatic 5:extra*/
	void setRank(int rank);
	void setNowScore(long score);
	void setHightScore(long score);

	static void setNowBomb(int count);
	static void setNowLife(int life);

	static void setMaxBomb(int  count);
	static void setMaxLife(int count);
};
#endif