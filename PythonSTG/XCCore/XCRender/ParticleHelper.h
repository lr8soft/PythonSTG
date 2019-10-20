#pragma once
#ifndef _FX_PARTICLE_GENERATER_H_
#define _FX_PARTICLE_GENERATER_H_
#include <list>
#include "RenderObject.h"
#include "SpecialEffect/XCParticle.h"
#include <glm/glm.hpp>
#include "../../util/GameTimer.h"
class ParticleHelper :public RenderObject{
private:
	XCGameTimer timer;
	std::list<ParticleInfo> particleManager;
public:
	virtual void Init() override;
	virtual void Render() override;
	virtual void Release() override;
	void addNewParticle(int density, float size,float velocity ,float lifetime,glm::vec4 color ,glm::vec3 pos);
};
#endif