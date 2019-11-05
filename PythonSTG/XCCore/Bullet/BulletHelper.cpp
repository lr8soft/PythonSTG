#include "BulletHelper.h"
#include "CircleTypeBullet.h"
#include "OvalTypeBullet.h"
#include "RectangleTypeBullet.h"
#include "LaserTypeBullet.h"
#include "../../XCInterpreter/ScriptLoader.h"
#include "../../XCInterpreter/ImageParseHelper.h"
Bullet * BulletHelper::getNewBulletObject(std::string bulletImage,std::string bulletType, glm::vec4 divideInfo, glm::vec3 scaleInfo, glm::vec3 collideSize,
	glm::vec3 initCoord, float velocity, float acceleration, float angle, float increateAngle, int reboundTime, bool aimPlayer,
	int particleDensity, float particleFinishTime, float particleVelocity, float particleSize, glm::vec4 particleColor)
{
	Bullet *bullet = nullptr;
	if (bulletType == "circleTypeBullet") {
		bullet = new CircleTypeBullet(bulletImage, divideInfo, scaleInfo, collideSize, initCoord, velocity, acceleration, angle, increateAngle, reboundTime, aimPlayer,
			particleDensity, particleFinishTime,  particleVelocity, particleSize, particleColor);
	}
	else if (bulletType == "ovalTypeBullet") {
		bullet = new OvalTypeBullet(bulletImage, divideInfo, scaleInfo, collideSize, initCoord, velocity, acceleration, angle, increateAngle, reboundTime, aimPlayer,
			particleDensity, particleFinishTime, particleVelocity, particleSize, particleColor);
	}
	else if (bulletType == "rectangleTypeBullet") {
		bullet = new RectangleTypeBullet(bulletImage, divideInfo, scaleInfo, collideSize, initCoord, velocity, acceleration, angle, increateAngle, reboundTime, aimPlayer,
			particleDensity, particleFinishTime, particleVelocity, particleSize, particleColor);
	}
	else if (bulletType == "laserTypeBullet") {
		bullet = new LaserTypeBullet(bulletImage, divideInfo, scaleInfo, collideSize, initCoord, velocity, acceleration, angle, increateAngle, reboundTime, aimPlayer,
			particleDensity, particleFinishTime, particleVelocity, particleSize, particleColor);
	}
	return bullet;
}

Bullet * BulletHelper::parseBulletObject(PyObject * bulletObject)
{
	Bullet* bullet = nullptr;

	if (bulletObject != nullptr) {
		PyObject* bulletGenerateInfo = PyObject_CallMethod(bulletObject, "_cpp_getGenerateInfo", NULL);
		PyObject* bulletCoordInfo = PyObject_CallMethod(bulletObject, "_cpp_getInitCoord", NULL);
		PyObject* bulletReleaseInfo = PyObject_CallMethod(bulletObject, "_cpp_getReleaseParticleInfo", NULL);
		PyObject* bulletTypeInfo = PyObject_CallMethod(bulletObject, "_cpp_getBulletInfo", NULL);
		ImageInfo bulletImageInfo = ImageParseHelper::parseImageHelperFromObject(bulletObject);

		const char* bulletType;
		PyArg_Parse(bulletTypeInfo, "s", &bulletType);

		float velocity, acceleration, angle, increaseAngle, collideSize[3]; int aimPlayer, reboundTime;
		PyArg_ParseTuple(bulletGenerateInfo, "ffffip(fff)", &velocity, &acceleration, &angle, &increaseAngle, &reboundTime, &aimPlayer, 
			&collideSize[0], &collideSize[1], &collideSize[2]);

		float initCoord[3];
		PyArg_ParseTuple(bulletCoordInfo, "fff", &initCoord[0], &initCoord[1], &initCoord[2]);

		int particleDensity; float lifeTime, particleVelocity, particleSize; float particleColor[4];
		PyArg_ParseTuple(bulletReleaseInfo, "ifff(ffff)", &particleDensity, &lifeTime, &particleVelocity, &particleSize,
			&particleColor[0], &particleColor[1], &particleColor[2], &particleColor[3]);

		bullet = BulletHelper::getNewBulletObject(bulletImageInfo.imagePath, bulletType, 
			glm::vec4(bulletImageInfo.divideColumn, bulletImageInfo.divideRow, bulletImageInfo.selectX, bulletImageInfo.selectY),
			glm::vec3(bulletImageInfo.zoomX, bulletImageInfo.zoomY, 0.1f),glm::vec3(collideSize[0], collideSize[1], collideSize[2]),
			glm::vec3(initCoord[0], initCoord[1], initCoord[2]), velocity, acceleration, angle, increaseAngle, reboundTime, aimPlayer,
			particleDensity, lifeTime, particleVelocity,particleSize, glm::vec4(particleColor[0], particleColor[1], particleColor[2], particleColor[3]));
		if (bullet != nullptr) {
			bullet->Init();
		}
	}

	return bullet;
}
