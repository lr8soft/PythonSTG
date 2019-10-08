#include "BulletHelper.h"
#include "CircleTypeBullet.h"
#include "../../XCInterpreter/ScriptLoader.h"
Bullet * BulletHelper::getNewBulletObject(std::string bulletImage,std::string bulletType, glm::vec4 divideInfo, glm::vec3 scaleInfo, glm::vec3 collideSize,
	glm::vec3 initCoord, float velocity, float acceleration, float angle, float increateAngle, int reboundTime, bool aimPlayer,
	int particleDensity, float particleFinishTime, float particleVelocity, float particleSize, glm::vec4 particleColor)
{
	Bullet *bullet = nullptr;
	if (bulletType == "circleTypeBullet") {
		bullet = new CircleTypeBullet(bulletImage, divideInfo, scaleInfo, collideSize, initCoord, velocity, acceleration, angle, increateAngle, reboundTime, aimPlayer,
			particleDensity, particleFinishTime,  particleVelocity, particleSize, particleColor);
	}
	return bullet;
}

Bullet * BulletHelper::parseBulletObject(PyObject * bulletObject)
{
	Bullet* bullet = nullptr;

	if (bulletObject != nullptr) {
		auto imageInfo = PyObject_CallMethod(bulletObject, "_cpp_getInitRenderInfo", NULL);
		auto bulletGenerateInfo = PyObject_CallMethod(bulletObject, "_cpp_getGenerateInfo", NULL);
		auto bulletCoordInfo = PyObject_CallMethod(bulletObject, "_cpp_getInitCoord", NULL);
		auto bulletReleaseInfo = PyObject_CallMethod(bulletObject, "_cpp_getReleaseParticleInfo", NULL);

		const char* bulletImage, *bulletType; int divideInfo[4]; float scaleInfo[3], collideSize[3];
		PyArg_ParseTuple(imageInfo, "ss(iiii)(fff)(fff)", &bulletImage, &bulletType, &divideInfo[0], &divideInfo[1], &divideInfo[2], &divideInfo[3],
			&scaleInfo[0], &scaleInfo[1], &scaleInfo[2], &collideSize[0], &collideSize[1], &collideSize[2]);


		float velocity, acceleration, angle, increaseAngle; int aimPlayer, reboundTime;
		PyArg_ParseTuple(bulletGenerateInfo, "ffffip", &velocity, &acceleration, &angle, &increaseAngle, &reboundTime, &aimPlayer);

		float initCoord[3];
		PyArg_ParseTuple(bulletCoordInfo, "fff", &initCoord[0], &initCoord[1], &initCoord[2]);

		int particleDensity; float lifeTime, particleVelocity, particleSize; float particleColor[4];
		PyArg_ParseTuple(bulletReleaseInfo, "ifff(ffff)", &particleDensity, &lifeTime, &particleVelocity, &particleSize,
			&particleColor[0], &particleColor[1], &particleColor[2], &particleColor[3]);

		bullet = BulletHelper::getNewBulletObject(bulletImage, bulletType, glm::vec4(divideInfo[0], divideInfo[1], divideInfo[2], divideInfo[3]),
			glm::vec3(scaleInfo[0], scaleInfo[1], scaleInfo[2]),glm::vec3(collideSize[0], collideSize[1], collideSize[2]), 
			glm::vec3(initCoord[0], initCoord[1], initCoord[2]), velocity, acceleration, angle, increaseAngle, reboundTime, aimPlayer,
			particleDensity, lifeTime, particleVelocity,particleSize, glm::vec4(particleColor[0], particleColor[1], particleColor[2], particleColor[3]));
		if (bullet != nullptr) {
			bullet->BulletInit();
		}
	}

	return bullet;
}
