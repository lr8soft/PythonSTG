#pragma once
#include "Bullet.h"
#include <string>
#include <map>
#include <glm/glm.hpp>
class BulletHelper {
public:
	static Bullet* getNewBulletObject(std::string bulletType, int bulletColor, glm::vec4 divideInfo, glm::vec3 scaleInfo, glm::vec3 initCoord
		, float velocity, float acceleration, float angle, float increateAngle, bool aimPlayer);
};