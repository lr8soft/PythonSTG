#pragma once
#ifndef _XCPlayer_H_
#define _XCPlayer_H_
#include <thread>
#include <atomic>
#include <map>
#include "../XCAudio/AudioHelper.h"
#include "../XCRender/SpecialEffect/DecisionPointSE.h"
#include "../XCRender/XCImageHelper.h"
class Player {
private:
	std::string itemUuid;
	bool itemWorkFinish = false;
	XCGameTimer itemTimer;

	IRenderHelper* renderHelper, *moonEffectHelper;

	bool isHitTime = false;
	double HitProtectTime = 3.0f;
	double lastHitTime = 0;
	long playerScore = 0.0;
	long double lastShootTime = 0;

	glm::vec4 divideInfo;
	glm::vec4 coverColor;
	glm::vec3 scaleSize;
	glm::vec3 rotateWork;

	glm::vec4 tempColor;

	float rotateAngle = 0.0f;
	float NowPosition[3] = { 0.0f ,-0.5f ,0.0f };

	DecisionPointSpecialEffect* specialEffectDecision;
	XCWavFile playerHurtAudio, playerGrazeAudio, playerExtentAudio;

	bool isInit = false, renderDecisionPoint = false, isMoonState = false;
	const char* playerFrameName, *playerImage;
	float basePower = 1.0f;
	float baseSpeed = 1.45f;
	float imageSwapTime = 0.08;
	enum playerState { PLAYER_STANDBY, PLAYER_TURNRIGHT, PLAYER_TURNLEFT };
	int playerLastState = PLAYER_STANDBY, playerNowState = PLAYER_STANDBY;
	int standByRow = 3, turnLeftRow = 2, turnRightRow = 1;
	float playerSameStateTime = 0.0f;

	int maxLife = 8, maxBomb = 8;
	int nowLife = 2, nowBomb = 2;

	int moonPoint = 0, maxMoonPoint = 50;
	int moonLevel = 100, maxMoonLevel = 100;
	double lastStartMoonTime = 0.0;

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
	void PlayerInit();
	void PlayerRender();
	void PlayerRelease();

	float* getPosition();
	void hurtPlayer();
	void grazePlayer();

	void addPower();
	void addPoint();
	void addLife();
	void addBomb();
	void addMoonPoint();
};
#endif