#include "ExplodeParticleGroupSE.h"

ExplodeParticleSpecialEffect::ExplodeParticleSpecialEffect(int density,float size ,float lifeTime,glm::vec4 color)
{
	groupDensity = density;
	groupColor = color;
	groupLifeTime = lifeTime;
	groupSize = size;
}

void ExplodeParticleSpecialEffect::SpecialEffectInit()
{
	for (int i = 0; i < groupDensity; i++) {
		XCParticle* particle = new XCParticle(groupLifeTime);
		particle->particleInit();

		particleGroup.push_back(particle);
	}
}

void ExplodeParticleSpecialEffect::SpecialEffectRender(float x, float y, float z)
{
	std::vector<XCParticle*>::iterator partBegin = particleGroup.begin();
	std::vector<XCParticle*>::iterator partEnd = particleGroup.end();
	for (auto particle = partBegin; particle != partEnd; particle++) {
		if (!(*particle)->getIsFinish()) {
			(*particle)->particleRender(glm::vec3(x, y, z), groupSize, groupColor);
		}
		if ((*particle)->getIsFinish()) {
			(*particle)->particleRelease();
			delete (*particle);
			if (std::next(particle) == particleGroup.end()) {
				particleGroup.erase(particle);
				break;
			}
			else {
				particle = particleGroup.erase(particle);
				partEnd = particleGroup.end();
			}
		}
	}
}

void ExplodeParticleSpecialEffect::SpecialEffectRelease()
{
}

bool ExplodeParticleSpecialEffect::getIsFinish()
{
	return false;
}
