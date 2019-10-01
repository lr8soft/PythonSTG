#pragma once
#ifndef _XCBULLET_H_
#define _XCBULLET_H_
#include <glm/glm.hpp>
#include "../../XCFrameInfo.h"
class Bullet {
protected:

	float NowPosition[3] = { 0.0f,  0.0f, 0.0f };

	bool isWorkFinish = false;

	void checkReboundOrOverflow(int *reBoundTimePointer, float *angle)
	{
		float frameWidth = XCFrameInfo::FrameRight;
		float frameHeight = XCFrameInfo::FrameTop;

		float renderX = NowPosition[0] * frameWidth;
		float renderY = NowPosition[1] * frameHeight;

		int reBoundTime = *reBoundTimePointer;
		if (renderY > frameHeight || renderY < -frameHeight
			|| renderX > frameWidth || renderX < -frameWidth) {
			if (reBoundTime > 0 || reBoundTime < 0) {// reBoundTime <0 ---> always rebound.
				if (renderX > frameWidth) {//right border
					if ((*angle) > 270.0f) {// (*angle) > 270*
						float delta = 90.0f - (180.0f - (*angle));
						(*angle) -= 2 * delta;
					}
					else {
						float delta = 90.0f - (*angle);
						(*angle) += 2 * delta;
					}
				}
				else if (renderX < -frameWidth) {//left border
					if ((*angle) > 180.0f) {
						float delta = 270.0f - (*angle);
						(*angle) += 2 * delta;
					}
					else {
						float delta = 270.0f - (180.0f - (*angle)) - 180.0f;
						(*angle) -= 2 * delta;
					}
				}
				else if (renderY > frameHeight) {// top boreder
					if ((*angle) < 90.0f) {
						float delta = 360.0f - (*angle);
						(*angle) = delta;
					}
					else {
						(*angle) += 2 * (180.0f - (*angle));
					}
				}
				else if (renderY < -frameHeight) {
					if ((*angle) > 270.0f) {
						(*angle) = 360.0f - (*angle);
					}
					else {
						(*angle) = 180.0f - ((*angle) - 180.0f);
					}
				}
				(*reBoundTimePointer)--;
			}
			else {
				isWorkFinish = true;
			}
		}
	}
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