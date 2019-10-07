#pragma once
#include "Bullet.h"
#include <string>
#include <glm/glm.hpp>
#include <Python.h>
class BulletHelper {
private:
	static Bullet* getNewBulletObject(std::string bulletImage,std::string bulletType, glm::vec4 divideInfo, glm::vec3 scaleInfo, glm::vec3 initCoord
		, float velocity, float acceleration, float angle, float increateAngle, int reboundTime, bool aimPlayer);
public:
	static  Bullet* parseBulletObject(PyObject* taskUnitItem);
};