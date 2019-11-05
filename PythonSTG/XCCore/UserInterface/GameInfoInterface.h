#pragma once
#ifndef _GAME_INFO_INTERFACE_H_
#define _GAME_INFO_INTERFACE_H_
#include "IUserInterface.h"
#include "../../util/GameTimer.h"
#include "../XCRender/XCAdvImageHelper.h"
#include "../XCRender/XCFont.h"
#define GameInfoUIUuid "gameInfo"
class GameInfoInterface :public IUserInterface{
protected:
	/*
	bool isInit = false, pauseGame = false, workFinish = false;
	*/
	int gameRank = 4;
	long nowScore = 0, highScore = LONG_MAX;

	float spellCardRemainTime = 0.0f;

	XCGameTimer timer;

	static int nowLife , maxLife ;
	static int nowBomb , maxBomb ;

	long moonPoint = 0, maxMoonPoint = 50;
	int moonLevel = 0, maxLevel = 100;
	float moonIndex = 0.0f;

	XCAdvImageHelper *rankImage, *playerInfoImage1, *playerInfoImage2, *lifeBombImage, *moonUIImage, *moonUIContext;
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
	void setSpellCardRemainTime(float time);

	static void setNowBomb(int count);
	static void setNowLife(int life);

	static void setMaxBomb(int  count);
	static void setMaxLife(int count);

	void setMoonPoint(long currentPoint, long maxPoint);
	void setMoonLevel(int level, int maxLevel);
};
#endif