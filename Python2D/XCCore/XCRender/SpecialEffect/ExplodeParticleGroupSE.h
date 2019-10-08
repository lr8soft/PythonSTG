#pragma once
#ifndef _PARTICLE_GROUP_SE_H_
#define _PARTICLE_GROUP_SE_H_
#include "XCParticle.h"
#include "../../../util/GameTimer.h"
#include <glm/glm.hpp>
#include <vector>
struct ParticleInfo {
	float x =0.0f, y = 0.0f, z = 0.0f;
	float velocity = 0.01f, angle = 0.0f;
};
class ExplodeParticleSpecialEffect {
private:
	int groupDensity;
	float groupSize;
	float groupLifeTime;
	float groupVelocity;
	glm::vec4 groupColor;
	glm::vec3 groupCoord;

	XCGameTimer timer;
	std::vector<XCParticle*> particleGroup;
	std::vector<ParticleInfo> particleInfoGroup;
public:
	ExplodeParticleSpecialEffect(int density,float size ,float lifetime, float velocity,glm::vec4 color, glm::vec3 initCoord);
	void SpecialEffectInit();
	void SpecialEffectRender();
	void SpecialEffectRelease();

	bool getIsFinish();
};
#endif