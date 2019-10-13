#include "EnemyObject.h"
#include <GL3/gl3w.h>
#include "../../XCFrameInfo.h"

EnemyObject::EnemyObject(IRenderHelper *ptr, glm::vec2 dInfo, glm::vec3 sInfo, glm::vec2 sbInfo, glm::vec2 wInfo,
	glm::vec3 iCoord, float v, float a, float agle, float agleA, int type)
{
	imageHelper = ptr;
	divideInfo = dInfo;
	scaleInfo = sInfo;
	standbyInfo = sbInfo;
	walkInfo = wInfo;
	NowPosition = iCoord;

	velocity = v;
	acceleration = a;
	angle = agle;
	angleAcceleration = agleA;

	colorType = type;
}

void EnemyObject::Init()
{
	if ((angle == 0 && velocity == 0) || angle == 270.0f || angle == 90.0f) {
		nowTexIndex = standbyInfo[0];
	}
	else {
		nowTexIndex = walkInfo[0];
	}
}

void EnemyObject::Render()
{
	timer.Tick();
	float deltaTime = timer.getDeltaFrame();
	float pi = 3.1415926535f;
	NowPosition[0] += velocity * cos(angle / 180.0f * pi) * deltaTime;
	NowPosition[1] += velocity * sin(angle / 180.0f * pi) * deltaTime;
	angle += angleAcceleration * deltaTime;
	velocity += acceleration * deltaTime;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	bool isAnti = false;
	if ((angle == 0 && velocity == 0) || angle == 270.0f || angle == 90.0f) {
		if (nowTexIndex < standbyInfo[1])
			nowTexIndex += 8.0f * deltaTime;
		else
			nowTexIndex = standbyInfo[0];
	}
	else {
		if (nowTexIndex < walkInfo[1])
			nowTexIndex += 8.0f * deltaTime;
		else
			nowTexIndex = walkInfo[0];

		if (angle >= 90.0f && angle <= 270.0f) {
			isAnti = true;
		}
	}

	imageHelper->Render(NowPosition, glm::vec4(1.0f), glm::radians(isAnti ? 180.0f : 0.0f), glm::vec3(0, 1, 0), scaleInfo,
		IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, divideInfo[0], divideInfo[1], (int)nowTexIndex, colorType));

	glDisable(GL_BLEND);

	float frameWidth = XCFrameInfo::FrameRight, frameHeight = XCFrameInfo::FrameTop;
	float renderWidth = scaleInfo[0] * XCFrameInfo::FrameRight;
	float renderHeight = scaleInfo[1] * XCFrameInfo::FrameTop;
	float renderX = NowPosition[0] * frameWidth, renderY = NowPosition[1] * frameHeight;
	if (renderY - renderHeight > frameHeight || renderY + renderHeight< -frameHeight
		|| renderX - renderWidth  > frameWidth || renderX + renderWidth < -frameWidth) {
		isWorkFinish = true;
	}
}

void EnemyObject::Release()
{
	imageHelper->Release();
	delete imageHelper;
}

