#include "FlexibleParticleGenerater.h"
#include "../../XCFrameInfo.h"
void FlexibleParticleGenerater::ManagerWork()
{
	timer.Tick();
	std::list<ParticleInfo>::iterator workBegin = particleManager.begin();
	std::list<ParticleInfo>::iterator workEnd = particleManager.end();
	for (auto particleObj = workBegin; particleObj != workEnd; particleObj++) {
		if (!particleObj->particle->getIsFinish()) {
			particleObj->x += particleObj->velocity * cos(particleObj->angle / 180.0f * 3.1415926f) * timer.getDeltaFrame();
			particleObj->y += particleObj->velocity * sin(particleObj->angle / 180.0f * 3.1415926f) * timer.getDeltaFrame();
			particleObj->particle->particleRender(
				glm::vec3(particleObj->x, particleObj->y, particleObj->z) * glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0F),
				particleObj->size, particleObj->color);
		}
		if (particleObj->particle->getIsFinish()) {
			particleObj->particle->particleRelease();
			delete (particleObj->particle);
			//particleObj = particleManager.erase(particleObj);
			//workEnd = particleManager.end();
			if (std::next(particleObj) == particleManager.end()) {
				particleManager.erase(particleObj);
				return;
			}
			else {
				particleObj = particleManager.erase(particleObj);
				workEnd = particleManager.end();
			}
		}
	}
}

void FlexibleParticleGenerater::addNewParticle(int density, float size, float velocity, float lifetime, glm::vec4 color, glm::vec3 pos)
{
	for (int i = 0; i < density; i++) {
		XCParticle* particle = new XCParticle(lifetime * rand() / (RAND_MAX + 1.0));
		particle->particleInit();

		ParticleInfo info;
		info.particle = particle;
		info.velocity = velocity * rand() / (RAND_MAX + 1.0);
		info.angle = (float)(rand() % 360);
		info.color = color;
		info.size = size;
		info.x = pos[0];
		info.y = pos[1];
		info.z = pos[2];

		particleManager.push_back(info);
	}
}
