#pragma once
#ifndef _TASK_INSIDE_ENEMY_UNIT_H_
#define _TASK_INSIDE_ENEMY_UNIT_H_
#include "../Enemy/EnemyObject.h"
#include "TaskInsideUnit.h"
class TaskEnemy : public TaskInsideUnit {
protected:
/*	int waitFrame, workInterval = 0, repeatTime = 0;
	bool haveAddToQueue = false, isFinish = false;
	std::list<RenderObject*> renderObjectGroup;
	std::string parentUuid;
*/
	std::string imagePath;
	glm::vec2 divideInfo;
	glm::vec3 scaleInfo;
	glm::vec2 standbyInfo;
	glm::vec2 walkInfo;
	glm::vec3 initCoord;
	int colorType;
	float velocity = 0.0f, acceleration = 0.0f, angle = 0.0f, angleAcceleration = 0.0f;

	EnemyObject* enemyImage = nullptr;
public:
	TaskEnemy(std::string uuid, int waitFrame, int workInterval, int repeatTime,
		std::string enemyImage, glm::vec2 divideInfo, glm::vec3 scaleInfo,glm::vec2 standbyInfo, glm::vec2 walkInfo,
		glm::vec3 initCoord, float velocity, float acceleration, float angle, float angleAcceleration, int type);
	virtual void UnitInit() override;
	virtual void UnitWork() override;
	virtual void UnitRelease() override;
};
#endif