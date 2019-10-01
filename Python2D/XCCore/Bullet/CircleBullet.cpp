#include "CircleBullet.h"
#include "../../XCFrameInfo.h"
#include <GL3/gl3w.h>
#include <iostream>
CircleBullet::CircleBullet(int bColor, glm::vec4 dInfo, glm::vec3 sInfo, glm::vec3 initCoord, float v, float a, float agl, float incA, int rbTime,bool ap)
{
	bulletColor = bColor;
	divideInfo = dInfo;
	scaleInfo = sInfo;
	NowPosition[0] = initCoord[0];
	NowPosition[1] = initCoord[1];
	NowPosition[2] = initCoord[2];
	velocity = v;
	acceleration = a;
	angle = agl;
	increaseAngle = incA;
	reBoundTime = rbTime;
	aimToPlayer = ap;

}

void CircleBullet::BulletInit()
{
	if (!isInit) {
		image = new XCImageHelper("assets/Bullet/bullet0.png", true);
		isInit = true;
	}
}

void CircleBullet::BulletRender()
{
	if (isInit) {
		timer.Tick();

		NowPosition[0] += velocity * cos(angle / 180.0f * 3.1415926f);
		NowPosition[1] += velocity * sin(angle / 180.0f * 3.1415926f);
		angle += increaseAngle;
		velocity += acceleration;
		checkOutOfScreen();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		image->Render(glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]), glm::vec4(1.0f), 0.0f, glm::vec3(1, 0, 0), scaleInfo,
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight,XCFrameInfo::FrameTop, divideInfo[0], divideInfo[1],bulletColor, divideInfo[3]));
		glDisable(GL_BLEND);
		
	}
}
void CircleBullet::checkOutOfScreen()
{
	float renderX = NowPosition[0] * XCFrameInfo::FrameRight;
	float renderY = NowPosition[1] * XCFrameInfo::FrameTop;
	if (renderY > XCFrameInfo::FrameTop || renderY < -( XCFrameInfo::FrameTop)
		|| renderX > XCFrameInfo::FrameRight || renderX < -(XCFrameInfo::FrameRight)) {
		if (reBoundTime > 0 || reBoundTime < 0) {// reBoundTime <0 ---> always rebound.
			if (renderX > XCFrameInfo::FrameRight) {//right border
				if (angle > 270.0f) {// angle > 270*
					float delta = 90.0f - (180.0f - angle);
					angle -= 2 * delta;
				}
				else {
					float delta = 90.0f - angle;
					angle += 2 * delta;
				}
			}
			else if(renderX < -(XCFrameInfo::FrameRight)){//left border
				if (angle > 180.0f) {
					float delta = 270.0f - angle;
					angle += 2 * delta;
				}
				else {
					float delta = 270.0f - (180.0f - angle) - 180.0f;
					angle -= 2 * delta;
				}
			}
			else if(renderY > XCFrameInfo::FrameTop){// top boreder
				if (angle  < 90.0f) {
					float delta = 360.0f - angle;
					angle = delta;
				}
				else {
					angle += 2 * (180.0f - angle);
				}
			}
			else if(renderY < -(XCFrameInfo::FrameTop)){
				if (angle > 270.0f) {
					angle = 360.0f - angle;
				}
				else {
					angle = 180.0f - (angle - 180.0f);
				}
			}
			reBoundTime--;
		}
		else {
			isWorkFinish = true;
		}
	}
}
void CircleBullet::BulletRelease()
{
	if (isInit) {
		image->Release();
		delete image;
		isInit = false;
	}
}
