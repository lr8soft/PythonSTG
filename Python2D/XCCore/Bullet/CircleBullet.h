#pragma once
#ifndef _CIRCLE_BULLET_H_
#define _CIRCLE_BULLET_H_
#include "Bullet.h"
#include <glm/glm.hpp>
#include "../../util/GameTimer.h"
#include "../XCRender/XCImageHelper.h"
class CircleBullet :public Bullet {
private:
	/*
	float velocity = 0.0f, acceleration = 0.0f, angle = 0.0f;
	float NowPosition[3] = { 0.0f,  0.0f, 0.0f };
	bool isWorkFinish = false;
	*/
	glm::vec4 divideInfo;
	glm::vec3 scaleInfo;
	int bulletColor;
	float velocity = 0.0f, acceleration = 0.0f, angle = 0.0f, increaseAngle = 0.0f;

	XCGameTimer timer;
	XCImageHelper* image;
	bool isInit = false, aimToPlayer = false;

	void checkOutOfScreen();
public:
	CircleBullet(int bulletColor, glm::vec4 divideInfo, glm::vec3 scaleInfo, glm::vec3 initCoord
		, float velocity, float acceleration, float angle, float increateAngle, bool aimPlayer);
	virtual void BulletInit()  override;
	virtual void BulletRender() override;
	virtual void BulletRelease() override;
};
#endif