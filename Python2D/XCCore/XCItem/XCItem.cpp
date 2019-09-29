#include "XCItem.h"
#include "../../XCFrameInfo.h"
#include <GLFW/glfw3.h>
XCItem::XCItem(IRenderHelper* image, glm::vec4 dInfo, glm::vec4 color, glm::vec3 sSize, glm::vec3 rWork, float rAngle)
{
	renderHelper = image;
	divideInfo = dInfo;
	scaleSize = sSize;
	renderRotateWork = rWork;
	rotateAngle = rAngle;
	coverColor = color;
}

void XCItem::ItemInit()
{
	srand(glfwGetTimerValue());
	if (rand() % 2 ==0) {
		NowPosition[0] += (float)rand() / RAND_MAX /10.0f / 5.0f;
		if (rand() % 2 == 0) {
			NowPosition[1] += (float)rand() / RAND_MAX / 10.0f / 5.0f;
		}
		else {
			NowPosition[1] -= (float)rand() / RAND_MAX / 10.0f / 5.0f;
		}
	}
	else {
		NowPosition[0] -= (float)rand() / RAND_MAX / 10.0f / 5.0f;
		if (rand() % 2 == 0) {
			NowPosition[1] += (float)rand() / RAND_MAX / 10.0f / 5.0f;
		}
		else {
			NowPosition[1] -= (float)rand() / RAND_MAX / 10.0f / 5.0f;
		}
	}
	
}

void XCItem::ItemRender()
{
	if (renderHelper != nullptr) {
		itemTimer.Tick();

		NowPosition[1] -= XCFrameInfo::defaultGravity * itemTimer.getDeltaFrame();
		renderHelper->Render(
			glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]),
			coverColor,
			rotateAngle,
			renderRotateWork,
			scaleSize,
			IRenderHelper::GetSpecificTexWithRate(
				XCFrameInfo::FrameRight, XCFrameInfo::FrameTop,divideInfo[0], divideInfo[1], divideInfo[2], divideInfo[3])
		);

		if (NowPosition[1] > scaleSize[1] + XCFrameInfo::FrameTop || NowPosition[1] < -(scaleSize[1] + XCFrameInfo::FrameTop)) {
			itemWorkFinish = true;
		}
	}
}

void XCItem::ItemRelease()
{
	renderHelper->Release();
	delete renderHelper;
}

bool XCItem::getIsFinish()
{
	return itemWorkFinish;
}

float * XCItem::getPosition()
{
	return NowPosition;
}

void XCItem::setPosition(float x, float y, float z)
{
	NowPosition[0] = x;
	NowPosition[1] = y;
	NowPosition[2] = z;
}
