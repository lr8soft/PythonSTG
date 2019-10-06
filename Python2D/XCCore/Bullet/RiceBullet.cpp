#include "RiceBullet.h"
#include "../../XCFrameInfo.h"
#include <GL3/gl3w.h>
#include <iostream>
RiceBullet::RiceBullet(int bColor, glm::vec4 dInfo, glm::vec3 sInfo, glm::vec3 initCoord, float v, float a, float agl, float incA, int rbTime,bool ap)
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

void RiceBullet::BulletInit()
{
	if (!isInit) {
		image = new XCImageHelper("assets/Bullet/riceBullet.png", true);
		isInit = true;
	}
}

void RiceBullet::BulletRender()
{
	if (isInit) {
		timer.Tick();

		NowPosition[0] += velocity * cos(angle / 180.0f * 3.1415926f);
		NowPosition[1] += velocity * sin(angle / 180.0f * 3.1415926f);
		angle += increaseAngle;
		velocity += acceleration;
		Bullet::checkReboundOrOverflow(&reBoundTime, &angle);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		image->Render(glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]), glm::vec4(1.0f), 0.0f, glm::vec3(1, 0, 0), scaleInfo,
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight,XCFrameInfo::FrameTop, divideInfo[0], divideInfo[1],divideInfo[3],bulletColor ));
		glDisable(GL_BLEND);
		
	}
}
void RiceBullet::BulletRelease()
{
	if (isInit) {
		image->Release();
		delete image;

		isInit = false;
	}
}
