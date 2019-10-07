#pragma once
#ifndef _CIRCLE_TYPE_BULLET_H_
#define _CIRCLE_TYPE_BULLET_H_
#include "Bullet.h"
#include <glm/glm.hpp>
#include "../../util/GameTimer.h"
#include "../XCRender/XCImageHelper.h"
class CircleTypeBullet :public Bullet {
private:
	/*
	float velocity = 0.0f, acceleration = 0.0f, angle = 0.0f;
	float NowPosition[3] = { 0.0f,  0.0f, 0.0f };
	bool isWorkFinish = false;
	*/
	std::string imagePath;

	glm::vec4 divideInfo;
	glm::vec3 scaleInfo;
	int  reBoundTime = 0;
	float velocity = 0.0f, acceleration = 0.0f, angle = 0.0f, increaseAngle = 0.0f;

	XCGameTimer timer;
	XCImageHelper* image;
	bool isInit = false, aimToPlayer = false;
public:
	/*#£¡Attention scaleInfo will work both collide and render.
#£¡renderSize: scaleX * widthRate : scaleY * heightRate  ,collideSize : scaleX : scaleY*/
	CircleTypeBullet(std::string bulletImagePath, glm::vec4 divideInfo, glm::vec3 scaleInfo, glm::vec3 initCoord
		, float velocity, float acceleration, float angle, float increateAngle, int reboundTime, bool aimPlayer);
	virtual void BulletInit()  override;
	virtual void BulletRender() override;
	virtual void BulletRelease() override;

	virtual bool BulletCollideWithPoint(float x, float y) override;
};
#endif