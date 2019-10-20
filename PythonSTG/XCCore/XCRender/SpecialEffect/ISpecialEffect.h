#pragma once
#ifndef _ISPECIAL_EFFECT_H_
#define _ISPECIAL_EFFECT_H_
class ISpecialEffect {
protected:
	bool isInit = false;
public:
	virtual void SpecialEffectInit() = 0;
	virtual void SpecialEffectRender(float x, float y, float z) = 0;
	virtual void SpecialEffectRelease() = 0;

	bool getIsInit() {
		return isInit;
	}
};
#endif