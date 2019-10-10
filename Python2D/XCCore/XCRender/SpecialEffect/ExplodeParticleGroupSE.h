#pragma once
#ifndef _PARTICLE_GROUP_SE_H_
#define _PARTICLE_GROUP_SE_H_
#include "XCParticle.h"
#include "../../../util/GameTimer.h"
#include <glm/glm.hpp>
#include <vector>
class ExplodeParticleSpecialEffect {
private:
	int groupDensity;
	float groupSize;
	float groupLifeTime;
	float groupVelocity;
	glm::vec4 groupColor;
	glm::vec3 groupCoord;

	bool isCoordInit = false;
	XCGameTimer timer;
	std::vector<ParticleInfo> particleGroup;
public:
	ExplodeParticleSpecialEffect(int density,float size ,float lifetime, float velocity, glm::vec4 color);
	void SpecialEffectCoordInit(glm::vec3 initCoord);
	void SpecialEffectGLInit();
	void SpecialEffectRender();
	void SpecialEffectRelease();

	bool getIsFinish();
};
#endif