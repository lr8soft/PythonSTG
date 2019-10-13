#pragma once
#ifndef _ENEMY_OBJECT_H_
#define _ENEMY_OBJECT_H_
#include "../XCRender/RenderObject.h"
#include "../XCRender/IRenderHelper.h"
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
	float velocity = 0.0f, acceleration = 0.0f, angle = 0.0f, angleAcceleration = 0.0f;
public:
	EnemyObject(IRenderHelper*, glm::vec2 divideInfo, glm::vec3 scaleInfo, glm::vec2 standbyInfo, glm::vec2 walkInfo,
		glm::vec3 initCoord, float velocity, float acceleration, float angle, float angleAcceleration, int type);
	virtual void Init() override;
	virtual void Render() override;
	virtual void Release() override;
};
#endif