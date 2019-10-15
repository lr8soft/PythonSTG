#include "RectangleTypeBullet.h"
#include "../../XCFrameInfo.h"
#include <GL3/gl3w.h>
#include <iostream>
RectangleTypeBullet::RectangleTypeBullet(std::string bulletImagePath, glm::vec4 dInfo, glm::vec3 sInfo,glm::vec3 cSize ,glm::vec3 initCoord, float v, float a, float agl, float incA, int rbTime, bool ap)
{
	imagePath = bulletImagePath;

	divideInfo = dInfo;
	scaleInfo = sInfo;
	collideSize = cSize;
	NowPosition[0] = initCoord[0];
	NowPosition[1] = initCoord[1];
	NowPosition[2] = initCoord[2];

	velocity = v;
	acceleration = a;
	angle = agl;
	increaseAngle = incA;
	reBoundTime = rbTime;
	aimToPlayer = ap;

	//define current type
	setCurrentType(BulletType);
}

void RectangleTypeBullet::Init()
{
	if (!isInit) {
		image = new XCImageHelper(imagePath, true);
		isInit = true;
	}
}

void RectangleTypeBullet::Render()
{
	if (isInit) {
		timer.Tick();
		NowPosition[0] += velocity * cos(angle / 180.0f * 3.1415926f) * timer.getDeltaFrame();
		NowPosition[1] += velocity * sin(angle / 180.0f * 3.1415926f) * timer.getDeltaFrame();
		angle += increaseAngle * timer.getDeltaFrame();
		velocity += acceleration * timer.getDeltaFrame();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		image->Render(glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]), glm::vec4(1.0f), glm::radians(angle), glm::vec3(0, 0, 1),
			scaleInfo * glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f),
			IRenderHelper::GetSpecificTexture(divideInfo[0], divideInfo[1], divideInfo[2], divideInfo[3]));
		glDisable(GL_BLEND);
		if (Bullet::checkReboundOrOverflow(&reBoundTime, &angle, collideSize[0], collideSize[1])) {//超出边界不渲染结束特效
			isWorkFinish = true;
		}
	}
}
void RectangleTypeBullet::Release()
{
	if (isInit) {
		image->Release();
		delete image;

		isInit = false;
	}
}

bool RectangleTypeBullet::BulletCollideWithPoint(float x, float y, bool& haveGraze)
{
	return false;
}

void RectangleTypeBullet::setBulletTerminate()
{
}
