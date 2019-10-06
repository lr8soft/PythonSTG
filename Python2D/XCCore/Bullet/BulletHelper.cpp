#include "BulletHelper.h"
#include "HugeBullet.h"
#include "CircleBullet.h"
#include "RiceBullet.h"
#include "../../XCInterpreter/ScriptLoader.h"
Bullet * BulletHelper::getNewBulletObject(std::string bulletType, int bulletColor, glm::vec4 divideInfo, glm::vec3 scaleInfo, glm::vec3 initCoord
	, float velocity, float acceleration, float angle, float increateAngle, int reboundTime, bool aimPlayer)
{
	Bullet *bullet = nullptr;
	if (bulletType == "circleBullet") {
		bullet = new CircleBullet(bulletColor, divideInfo, scaleInfo, initCoord, velocity, acceleration, angle, increateAngle, reboundTime, aimPlayer);
	}
	else if (bulletType == "riceBullet") {
		bullet = new RiceBullet(bulletColor, divideInfo, scaleInfo, initCoord, velocity, acceleration, angle, increateAngle, reboundTime, aimPlayer);
	}
	else if (bulletType == "hugeBullet") {
		bullet = new HugeBullet(bulletColor, divideInfo, scaleInfo, initCoord, velocity, acceleration, angle, increateAngle, reboundTime, aimPlayer);
	}
	return bullet;
}

Bullet * BulletHelper::parseBulletObject(PyObject * bulletObject)
{
	Bullet* bullet = nullptr;

	if (bulletObject != nullptr) {
		auto imageInfo = PyObject_CallMethod(bulletObject, "_cpp_getInitRenderInfo", NULL);
		auto bulletColorInfo = PyObject_CallMethod(bulletObject, "_cpp_getBulletColor", NULL);
		auto bulletGenerateInfo = PyObject_CallMethod(bulletObject, "_cpp_getGenerateInfo", NULL);
		auto bulletCoordInfo = PyObject_CallMethod(bulletObject, "_cpp_getInitCoord", NULL);

		const char* bulletType; int divideInfo[4]; float scaleInfo[3];
		PyArg_ParseTuple(imageInfo, "s(iiii)(fff)", &bulletType, &divideInfo[0], &divideInfo[1], &divideInfo[2], &divideInfo[3], &scaleInfo[0], &scaleInfo[1], &scaleInfo[2]);

		int bulletColor;
		PyArg_Parse(bulletColorInfo, "i", &bulletColor);

		float velocity, acceleration, angle, increaseAngle; int aimPlayer, reboundTime;
		PyArg_ParseTuple(bulletGenerateInfo, "ffffip", &velocity, &acceleration, &angle, &increaseAngle, &reboundTime, &aimPlayer);

		float initCoord[3];
		PyArg_ParseTuple(bulletCoordInfo, "fff", &initCoord[0], &initCoord[1], &initCoord[2]);

		bullet = BulletHelper::getNewBulletObject(bulletType, bulletColor, glm::vec4(divideInfo[0], divideInfo[1], divideInfo[2], divideInfo[3])
			, glm::vec3(scaleInfo[0], scaleInfo[1], scaleInfo[2]), glm::vec3(initCoord[0], initCoord[1], initCoord[2])
			, velocity, acceleration, angle, increaseAngle, reboundTime, aimPlayer);
		if (bullet != nullptr) {
			bullet->BulletInit();
		}
	}

	return bullet;
}
