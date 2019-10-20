#pragma once
#ifndef _PARTICLE_GROUP_SE_H_
#define _PARTICLE_GROUP_SE_H_
#include "ISpecialEffect.h"
#include "XCParticle.h"
#include "../../../util/GameTimer.h"
#include <vector>
class ExplodeParticleSpecialEffect :public ISpecialEffect {
private:
	int groupDensity;
	float groupSize;
	float groupLifeTime;
	glm::vec4 groupColor;

	XCGameTimer timer;
	std::vector<XCParticle*> particleGroup;
public:
	ExplodeParticleSpecialEffect(int density,float size ,float lifetime,glm::vec4 color);
	virtual void SpecialEffectInit() override;
	virtual void SpecialEffectRender(float x, float y, float z) override;
	virtual void SpecialEffectRelease() override;

	bool getIsFinish();
};
#endif