#include "CircleBullet.h"
#include "../../XCFrameInfo.h"
#include <GL3/gl3w.h>
#include <iostream>
CircleBullet::CircleBullet(int bColor, glm::vec4 dInfo, glm::vec3 sInfo, glm::vec3 initCoord, float v, float a, float agl, float incA, bool ap)
{
	bulletColor = bColor;
	divideInfo = dInfo;
	scaleInfo = sInfo;
	NowPosition[0] = initCoord[0];
	NowPosition[1] = initCoord[1];
	NowPosition[2] = initCoord[2];
	velocity = v;
	acceleration = a;
	angle = agl / 180.0f * 3.1415926f;
	increaseAngle = incA;
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
		NowPosition[0] += velocity * cos(angle);
		NowPosition[1] += velocity * sin(angle);
		angle += increaseAngle;
		velocity += acceleration;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		image->Render(glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]), glm::vec4(1.0f), 0.0f, glm::vec3(1, 0, 0), scaleInfo,
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight,XCFrameInfo::FrameTop, divideInfo[0], divideInfo[1],bulletColor, divideInfo[3]));
		glDisable(GL_BLEND);
	//	checkOutOfScreen();
	}
}
void CircleBullet::checkOutOfScreen()
{
	if (NowPosition[1] > scaleInfo[1] + XCFrameInfo::FrameTop || NowPosition[1] < -(scaleInfo[1] + XCFrameInfo::FrameTop)
		|| NowPosition[0] > scaleInfo[0] + XCFrameInfo::FrameRight || NowPosition[0] < -(scaleInfo[0] + XCFrameInfo::FrameRight)) {
		isWorkFinish = true;
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
