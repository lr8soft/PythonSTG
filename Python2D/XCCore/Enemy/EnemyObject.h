#pragma once
#ifndef _ENEMY_OBJECT_H_
#define _ENEMY_OBJECT_H_
#include "../XCRender/RenderObject.h"
#include "../XCRender/IRenderHelper.h"
#include "../XCAudio/AudioHelper.h"
#include "../../util/GameTimer.h"
#include <glm/glm.hpp>
class EnemyObject :public RenderObject {
private:
	XCGameTimer timer;
	IRenderHelper* imageHelper = nullptr;
	glm::vec2 divideInfo;
	glm::vec3 scaleInfo;
	glm::vec2 standbyInfo;
	glm::vec2 walkInfo;
	glm::vec3 NowPosition;
	int colorType; float nowTexIndex = 0;
	float velocity = 0.0f, acceleration = 0.0f, angle = 0.0f, angleAcceleration = 0.0f, movingTime = -1.0f;
	float currentHealth = 0.0f;

	XCWavFile deadEffect;
public:
	EnemyObject(IRenderHelper*, glm::vec2 divideInfo, glm::vec3 scaleInfo, glm::vec2 standbyInfo, glm::vec2 walkInfo,
		glm::vec3 initCoord, float velocity, float movingTime, float acceleration, float angle, float angleAcceleration, int type, float health);
	virtual void Init() override;
	virtual void Render() override;
	virtual void Release() override;

	glm::vec3 getNowPosition();
	void hurtEnemy(float damage);
};
#endif