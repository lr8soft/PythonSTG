#pragma once
#ifndef _BOSS_OBJECT_H_
#define _BOSS_OBJECT_H_
#include "../XCRender/RenderObject.h"
#include "../XCRender/IRenderHelper.h"
#include "../XCRender/XCImageHelper.h"
#include "../XCAudio/AudioHelper.h"
#include "../../util/GameTimer.h"
#include <glm/glm.hpp>
class BossObject :public RenderObject{
protected:
	XCGameTimer timer;

	enum BossState {
		StandByState, WalkState, AttackState
	};
	BossState nowState = StandByState;
	float nowImageIndex = 0.0f;
	int nowImageState = 1;

	IRenderHelper* bossImage;

	glm::vec2 NowPosition = glm::vec2(0.0f, 1.2f);
	glm::vec2 divideInfo;
	glm::vec2 scaleInfo;
	int standByRow;
	int walkRow;
	int attackRow;

	float angle = 0.0f;
	const float speed = 0.8f;
	float velocity = 0.8f;
	float moveTime = 0.0f;
	bool finishMoving = true;

	bool isNowSpellCardHitPointClear = false;
	float nowHitPoint = 100.0f, maxHitPoint = 100.0f, spellCardTime = 0.0f;
	int spellCardCount = 1;

	XCWavFile damageNormal, damageFinal, bossExplode;

public:
	BossObject(IRenderHelper* helper, glm::vec2 divideInfo, glm::vec2 scaleInfo, int standByRow, int walkRow, int attackRow);
	virtual void Init() override;
	virtual void Render() override;
	virtual void Release() override;

	void setBossHitPoint(float hitPoint);
	void setBossSpellCardCount(int count);
	void setBossSpellCardTime(float time);
	void setMovement(const glm::vec2& movemet);
	bool getFinishMovement();

	void hurtBossObject(float damage);
	bool getSpellCardHitPointClear();
	glm::vec2 getPosition();
	float getBossCollisionRadius();

	void setSpellCardFinish(bool is);
	void setBossFinish(bool is);
};
#endif