#include "ExplodeParticleGroupSE.h"
#include "../../../XCFrameInfo.h"
ExplodeParticleSpecialEffect::ExplodeParticleSpecialEffect(int density,float size ,float lifeTime, float v,glm::vec4 color, glm::vec3 initCoord)
{
	groupDensity = density;
	groupColor = color;
	groupLifeTime = lifeTime;
	groupSize = size;
	groupCoord = initCoord;
	groupVelocity = v;
}

void ExplodeParticleSpecialEffect::SpecialEffectInit()
{
	for (int i = 0; i < groupDensity; i++) {
		XCParticle* particle = new XCParticle(groupLifeTime);
		ParticleInfo info;
		info.x = groupCoord.x;
		info.y = groupCoord.y;
		info.z = groupCoord.z;
		info.velocity = groupVelocity;
		info.angle = rand() % 360;

		particle->particleInit();

		particleGroup.push_back(particle);
		particleInfoGroup.push_back(info);
	}
}

void ExplodeParticleSpecialEffect::SpecialEffectRender()
{
	std::vector<XCParticle*>::iterator partBegin = particleGroup.begin();
	std::vector<XCParticle*>::iterator partEnd = particleGroup.end();

	std::vector<ParticleInfo>::iterator infoBegin = particleInfoGroup.begin();
	std::vector<ParticleInfo>::iterator infoEnd = particleInfoGroup.end();
	auto info = infoBegin;
	for (auto particle = partBegin; particle != partEnd && info != infoEnd; particle++, info++) {
		if (!(*particle)->getIsFinish()) {
			info->x += info->velocity * cos(info->angle / 180.0f * 3.1415926f) * timer.getDeltaFrame();
			info->y += info->velocity * sin(info->angle / 180.0f * 3.1415926f) * timer.getDeltaFrame();
			(*particle)->particleRender(glm::vec3(info->x, info->y, info->z) * glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0F), groupSize, groupColor);
		}
		if ((*particle)->getIsFinish()) {
			(*particle)->particleRelease();
			delete (*particle);
			if (std::next(particle) == particleGroup.end() && std::next(info) == particleInfoGroup.end()) {
				particleGroup.erase(particle);
				particleInfoGroup.erase(info);
				break;
			}
			else {
				particle = particleGroup.erase(particle);
				particleInfoGroup.erase(info);
				partEnd = particleGroup.end();
				infoEnd = particleInfoGroup.end();
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
