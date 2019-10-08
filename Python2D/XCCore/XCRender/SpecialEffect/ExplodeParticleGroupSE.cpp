#include "ExplodeParticleGroupSE.h"
#include "../../../XCFrameInfo.h"
ExplodeParticleSpecialEffect::ExplodeParticleSpecialEffect(int density,float size ,float lifeTime, float v,glm::vec4 color)
{
	groupDensity = density;
	groupColor = color;
	groupLifeTime = lifeTime;
	groupSize = size;

	groupVelocity = v;

}

void ExplodeParticleSpecialEffect::SpecialEffectCoordInit(glm::vec3 initCoord)
{
	if (!isCoordInit) {
		groupCoord = initCoord;
		for (int i = 0; i < particleGroup.size(); i++) {
			particleGroup[i].x = groupCoord.x;
			particleGroup[i].y = groupCoord.y;
			particleGroup[i].z = groupCoord.z;

			particleGroup[i].angle = (float)(rand() % 360);
			particleGroup[i].velocity = groupVelocity;
		}
		isCoordInit = true;
	}
}

void ExplodeParticleSpecialEffect::SpecialEffectGLInit()
{
	for (int i = 0; i < groupDensity; i++) {
		XCParticle* particle = new XCParticle(groupLifeTime);
		particle->particleInit();
	
		ParticleInfo info;
		info.particle = particle;

		particleGroup.push_back(info);
	}
}

void ExplodeParticleSpecialEffect::SpecialEffectRender()
{
	timer.Tick();
	std::vector<ParticleInfo>::iterator partBegin = particleGroup.begin();
	std::vector<ParticleInfo>::iterator partEnd = particleGroup.end();

	for (auto particleIter = partBegin; particleIter != partEnd; particleIter++) {

		if (!particleIter->particle->getIsFinish()) {
			particleIter->x += particleIter->velocity * cos(particleIter->angle / 180.0f * 3.1415926f) * timer.getDeltaFrame();
			particleIter->y += particleIter->velocity * sin(particleIter->angle / 180.0f * 3.1415926f) * timer.getDeltaFrame();
			particleIter->particle->particleRender(glm::vec3(particleIter->x, particleIter->y, particleIter->z) * glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0F), groupSize, groupColor);
		}
		if (particleIter->particle->getIsFinish()) {
			particleIter->particle->particleRelease();
			delete (particleIter->particle);
			if (std::next(particleIter) == particleGroup.end()) {
				particleGroup.erase(particleIter);
				break;
			}
			else {
				particleIter = particleGroup.erase(particleIter);
				partEnd = particleGroup.end();
			}
		}
	}
}

void ExplodeParticleSpecialEffect::SpecialEffectRelease()
{
	std::vector<ParticleInfo>::iterator partBegin = particleGroup.begin();
	std::vector<ParticleInfo>::iterator partEnd = particleGroup.end();
	for (auto iter = partBegin; iter != partEnd; iter++) {
		iter->particle->particleRelease();
		delete iter->particle;
		iter->particle = nullptr;
	}
	particleGroup.clear();
}

bool ExplodeParticleSpecialEffect::getIsFinish()
{
	return !particleGroup.empty();
}
