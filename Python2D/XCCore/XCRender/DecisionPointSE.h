#pragma once
#ifndef _DECISIONPOINT_SE_H_
#define _DECISIONPOINT_SE_H_
#include "ISpecialEffect.h"
#include "IRenderHelper.h"
#include "../../util/GameTimer.h"
class DecisionPointSpecialEffect:public ISpecialEffect {
private:
	XCGameTimer timer;
	IRenderHelper* image;
public:
	virtual void SpecialEffectInit() override;
	virtual void SpecialEffectRender(float x, float y, float z) override;
	virtual void SpecialEffectRelease() override;
};
#endif
