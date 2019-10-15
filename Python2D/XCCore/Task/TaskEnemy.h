#pragma once
#ifndef _TASK_INSIDE_ENEMY_UNIT_H_
#define _TASK_INSIDE_ENEMY_UNIT_H_
#include "../Enemy/EnemyObject.h"
#include "TaskInsideUnit.h"
#include "Task.h"
class TaskEnemy : public Task {
protected:
	std::string imagePath;
	glm::vec2 divideInfo;
	glm::vec3 scaleInfo;
	glm::vec2 standbyInfo;
	glm::vec2 walkInfo;
	glm::vec3 NowPosition;
	int colorType;

	bool haveImageAddInQueue = false;
	float velocity = 0.0f, acceleration = 0.0f, angle = 0.0f, angleAcceleration = 0.0f, movingTime = -1.0f;
	float nowLife = 0.0f;

	EnemyObject* enemyImage = nullptr;


	virtual void taskSubWork() override;
public:
	TaskEnemy(std::string taskUuid, std::vector<std::string> targetTaskUuid, int repeatTime, int intervalFrame ,
		std::string enemyImage, glm::vec2 divideInfo, glm::vec3 scaleInfo,glm::vec2 standbyInfo, glm::vec2 walkInfo,
		glm::vec3 initCoord, float velocity, float movingTime, float acceleration, float angle, float angleAcceleration, int type, float enemyHealth);
	virtual void TaskInit() override;
	virtual void TaskRelease() override;
};
#endif