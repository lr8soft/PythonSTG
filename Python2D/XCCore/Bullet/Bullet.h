#pragma once
#ifndef _XCBULLET_H_
#define _XCBULLET_H_
#include <glm/glm.hpp>
#include "../XCRender/RenderObject.h"
#include "../../XCFrameInfo.h"
class Bullet:public RenderObject {
protected:

	float NowPosition[3] = { 0.0f,  0.0f, 0.0f };
	/*
	boolisWorkFinish = false
	*/
	bool isFinishTime = false;

	bool checkReboundOrOverflow(int *reBoundTimePointer, float *angle, float scaleX, float scaleY)
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
				float renderWidth = scaleX * XCFrameInfo::FrameRight;
				float renderHeight = scaleY * XCFrameInfo::FrameTop;
				if (renderY - renderHeight   > frameHeight || renderY + renderHeight< -frameHeight
					|| renderX - renderWidth  > frameWidth || renderX + renderWidth  < -frameWidth) {
					return true;
				}
			}
		}
		return false;
	}

	/*if aimToPlayer==false ,playerPos can be nullptr.*/
	void solveBulletMovement(bool &aimToPlayer, float* playerPos,float &velocity, float &angle, float &acceleration, float &increaseAngle, float deltaTime) {
		float pi = 3.1415926535f;
		if (aimToPlayer) {
			if (playerPos != nullptr) {
				float x = *(playerPos), y = *(playerPos + 1);
				float k = (y - NowPosition[1]) / (x - NowPosition[0]);
				float theta = 0.0f;
				if (x != NowPosition[0]) {
					theta = atan(k);
				}
				else {
					if (y > NowPosition[1]) {
						theta = pi / 2.0f;
					}
					else {
						theta = (pi *3.0f) / 2.0f;
					}
				}
				if (x < NowPosition[0])
					velocity = -velocity;

				angle = (180.0f / pi) * theta;
				aimToPlayer = false;
			}
		}
		NowPosition[0] += velocity * cos(angle / 180.0f * pi) * deltaTime;
		NowPosition[1] += velocity * sin(angle / 180.0f * pi) * deltaTime;
		angle += increaseAngle * deltaTime;
		velocity += acceleration * deltaTime;
	}
public:
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	virtual bool BulletCollideWithPoint(float x, float y, bool &haveGraze) = 0;

	virtual void startFinishEffect() = 0;


	bool getIsFinishTime() {
		return isFinishTime;
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