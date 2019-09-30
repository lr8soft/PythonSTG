#pragma once
#ifndef _XCBULLET_H_
#define _XCBULLET_H_
#include <glm/glm.hpp>
class Bullet {
protected:

	float NowPosition[3] = { 0.0f,  0.0f, 0.0f };

	bool isWorkFinish = false;

	virtual void checkOutOfScreen() = 0;
public:
	virtual void BulletInit() = 0;
	virtual void BulletRender() = 0;
	virtual void BulletRelease() = 0;

	bool getIsFinish() {
		return isWorkFinish;
	}

	void setPosition(float x, float y, float z) {
		NowPosition[0] = x;
		NowPosition[1] = y;
		NowPosition[2] = z;
	}

	float* getPosition() {
		return NowPosition;
	}
};
#endif