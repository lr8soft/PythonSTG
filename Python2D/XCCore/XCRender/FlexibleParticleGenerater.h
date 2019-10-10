#pragma once
#ifndef _FX_PARTICLE_GENERATER_H_
#define _FX_PARTICLE_GENERATER_H_
#include <list>
#include "SpecialEffect/XCParticle.h"
#include <glm/glm.hpp>
#include "../../util/GameTimer.h"
class FlexibleParticleGenerater {
private:
	XCGameTimer timer;
	std::list<ParticleInfo> particleManager;
public:
	void ManagerWork();
	void addNewParticle(int density, float size,float velocity ,float lifetime,glm::vec4 color ,glm::vec3 pos);
};
#endif