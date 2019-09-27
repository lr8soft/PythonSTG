#pragma once
#ifndef _XCPlayer_H_
#define _XCPlayer_H_
#include "XCItem.h"
class XCPlayer:public XCItem {
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
	const float baseSpeed = 1.45f;
	enum playerState { PLAYER_STANDBY, PLAYER_TURNRIGHT, PLAYER_TURNLEFT };
	int playerLastState = PLAYER_STANDBY, playerNowState = PLAYER_STANDBY;
	float playerSameStateTime = 0.0f;

	void playerKeyCheck(); 
	void setPlayerDirection(int direction);
public:
	XCPlayer(std::string uuid, IRenderHelper* image, glm::vec4 divideInfo, glm::vec4 coverColor, glm::vec3 scaleSize,
		glm::vec3 rotateWork, float rotateAngle);
	virtual void ItemRender() override;
};
#endif