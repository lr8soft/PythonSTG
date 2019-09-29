#pragma once
#ifndef _XCPlayer_H_
#define _XCPlayer_H_
#include "Item.h"
#include <map>
#include "../XCRender/DecisionPointSE.h"
class Player:public Item {
private:
	/*
	std::string itemUuid;
	bool itemWorkFinish = false;
	XCGameTimer itemTimer;

	IRenderHelper* renderHelper;
	glm::vec4 divideInfo;
	glm::vec4 coverColor;
	glm::vec3 scaleSize;
	glm::vec3 rotateWork;
	float rotateAngle = 0.0f;

	float NowPosition[3] = {0.0f, 0.0f, 0.0f};
	*/
	DecisionPointSpecialEffect* specialEffectDecision;

	bool isInit = false, renderDecisionPoint = false;
	const char* playerFrameName, *playerImage;
	float basePower = 1.0f;
	float baseSpeed = 1.45f;
	float imageSwapTime = 0.08;
	enum playerState { PLAYER_STANDBY, PLAYER_TURNRIGHT, PLAYER_TURNLEFT };
	int playerLastState = PLAYER_STANDBY, playerNowState = PLAYER_STANDBY;
	int standByRow = 3, turnLeftRow = 2, turnRightRow = 1;
	float playerSameStateTime = 0.0f;

	void playerKeyCheck(); 
	void setPlayerDirection(int direction);
protected:
	static std::map<std::string, Player*> playerInstanceGroup;
public:
	static void addPlayerInstance(std::string, Player*);
	static std::map<std::string, Player*>* getPlayerGroup();
	Player(const char* image, glm::vec4 divideInfo, glm::vec4 coverColor, glm::vec3 scaleSize,
		glm::vec3 rotateWork, float rotateAngle, float moveSpeed, float imgSwapInterval, float basePower, int standByRow, int turnLeftRow, int turnRightRow);

	bool getIsInit();
	virtual void ItemInit() override;
	virtual void ItemRender() override;
	virtual void ItemRelease() override;
};
#endif