#include "BulletHelper.h"
#include "CircleBullet.h"
Bullet * BulletHelper::getNewBulletObject(std::string bulletType, int bulletColor, glm::vec4 divideInfo, glm::vec3 scaleInfo, glm::vec3 initCoord
	, float velocity, float acceleration, float angle, float increateAngle, bool aimPlayer)
{
	Bullet *bullet = nullptr;
	if (bulletType == "circleBullet") {
		bullet = new CircleBullet(bulletColor, divideInfo, scaleInfo, initCoord, velocity, acceleration, angle, increateAngle, aimPlayer);
	}
	return bullet;
}
