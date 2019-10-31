#include "AbsorbParticleHelper.h"
#include "../../XCFrameInfo.h"
void AbsorbParticleHelper::Init()
{
}
void AbsorbParticleHelper::Render()
{
	timer.Tick();
	std::list<ParticleInfo>::iterator workBegin = particleManager.begin();
	std::list<ParticleInfo>::iterator workEnd = particleManager.end();
	bool hChange = false;
	for (auto particleObj = workBegin; particleObj != workEnd; particleObj++) {
		if (!particleObj->particle->getIsFinish()) {
			if (timer.getAccumlateTime() >= 0.2f) {
				if (!haveChangeAngle) {
					float pi = 3.1415926f;
					float x = destCoord.x, y = destCoord.y;
					float k = (y - particleObj->y) / (x - particleObj->x);
					float theta = 0.0f;
					if (x != particleObj->x) {
						theta = atan(k);
					}
					else {
						if (y > particleObj->y) {
							theta = pi / 2.0f;
						}
						else {
							theta = (pi *3.0f) / 2.0f;
						}
					}
					if (x < particleObj->x)
						particleObj->velocity = -particleObj->velocity;

					particleObj->angle = (180.0f / pi) * theta;
					hChange = true;
				}
			}
			particleObj->x += particleObj->velocity * cos(particleObj->angle / 180.0f * 3.1415926f) * timer.getDeltaFrame();
			particleObj->y += particleObj->velocity * sin(particleObj->angle / 180.0f * 3.1415926f) * timer.getDeltaFrame();
			particleObj->particle->particleRender(
				glm::vec3(particleObj->x, particleObj->y, particleObj->z) * glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0F),
				particleObj->size, particleObj->color);
		}
		if (particleObj->particle->getIsFinish()) {
			particleObj->particle->particleRelease();
			delete (particleObj->particle);
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
	if (hChange) {
		haveChangeAngle = true;
	}
	if (particleManager.empty()) {
		isWorkFinish = true;
	}
}

void AbsorbParticleHelper::Release()
{
	if (!particleManager.empty()) {
		std::list<ParticleInfo>::iterator workBegin = particleManager.begin();
		std::list<ParticleInfo>::iterator workEnd = particleManager.end();
		for (auto particleObj = workBegin; particleObj != workEnd; particleObj++) {
			particleObj->particle->particleRelease();
			delete (particleObj->particle);
		}
		particleManager.clear();
	}
}

void AbsorbParticleHelper::addNewParticle(int density, float size, float velocity, float lifetime, glm::vec4 color, glm::vec2 pos, glm::vec2 dest)
{
	destCoord = dest;
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
		info.z = 0.0f;

		particleManager.push_back(info);
	}
}
