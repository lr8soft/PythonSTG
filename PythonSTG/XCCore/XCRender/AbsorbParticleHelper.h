#pragma once
#ifndef _ABS_PARTICLE_GENERATER_H_
#define _ABS_PARTICLE_GENERATER_H_
#include <list>
#include "RenderObject.h"
#include "SpecialEffect/XCParticle.h"
#include <glm/glm.hpp>
#include "../../util/GameTimer.h"
class AbsorbParticleHelper :public RenderObject {
private:
	XCGameTimer timer;
	std::list<ParticleInfo> particleManager;

	glm::vec2 destCoord;
	bool haveChangeAngle = false;
public:
	virtual void Init() override;
	virtual void Render() override;
	virtual void Release() override;
	void addNewParticle(int density, float size, float velocity, float lifetime, glm::vec4 color, glm::vec2 pos, glm::vec2 dest);
};
#endif