#pragma once
#ifndef _NORMAL_STRIKE_H_
#define _NORMAL_STRIKE_H_
#include "IAttack.h"
#include "../../util/GameTimer.h"
#include "../XCRender/XCImageHelper.h"
#include "../XCAudio/AudioHelper.h"
class NormalStrike:public IAttack {
protected:
	static XCWavFile strikeEffect;
	static bool isResInit;

	XCGameTimer timer;
	float scaleSize[3] = { 0.0f };
	float texIndex = 1.0f;
	float NowPosition[3] = {0.0f, 0.0f, 0.0f}, velocity = 2.0f;
	XCImageHelper *renderHelper;
	bool isInit = false, haveEffectPlay = false, isFinish = false;
	double finishTime = 0.0;
public:
	NormalStrike(float x, float y, float z = 0.0f);
	virtual void Init() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual void checkCollisonWithEnemy(EnemyObject* pEnemy) override;
};
#endif