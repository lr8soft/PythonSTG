#include "Item.h"
#include "../../XCFrameInfo.h"
#include <GLFW/glfw3.h>
Item::Item(IRenderHelper* image, glm::vec4 dInfo, glm::vec4 color, glm::vec3 sSize, glm::vec3 rWork, float rAngle)
{
	renderHelper = image;
	divideInfo = dInfo;
	scaleSize = sSize;
	rotateWork = rWork;
	rotateAngle = rAngle;
	coverColor = color;
}

void Item::ItemInit()
{
	auto randSeed = glfwGetTimerValue();
	srand(randSeed);
	if (rand() % 2 ==0) {
		NowPosition[0] += (float)rand() / RAND_MAX /10.0f / 3.0f;
		if (rand() % 2 == 0) {
			NowPosition[1] += (float)rand() / RAND_MAX / 10.0f / 3.0f;
		}
		else {
			NowPosition[1] -= (float)rand() / RAND_MAX / 10.0f / 3.0f;
		}
	}
	else {
		NowPosition[0] -= (float)rand() / RAND_MAX / 10.0f / 3.0f;
		if (rand() % 2 == 0) {
			NowPosition[1] += (float)rand() / RAND_MAX / 10.0f / 3.0f;
		}
		else {
			NowPosition[1] -= (float)rand() / RAND_MAX / 10.0f / 3.0f;
		}
	}
	
}

void Item::ItemRender()
{
	if (renderHelper != nullptr) {
		itemTimer.Tick();

		NowPosition[1] -= XCFrameInfo::defaultGravity * itemTimer.getDeltaFrame();
		renderHelper->Render(
			glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]),
			coverColor,
			rotateAngle,
			rotateWork,
			scaleSize,
			IRenderHelper::GetSpecificTexWithRate(
				XCFrameInfo::FrameRight, XCFrameInfo::FrameTop,divideInfo[0], divideInfo[1], divideInfo[2], divideInfo[3])
		);

		checkOutOfScreen();
	}
}
void Item::checkOutOfScreen()
{
	if (NowPosition[1] > scaleSize[1] + XCFrameInfo::FrameTop || NowPosition[1] < -(scaleSize[1] + XCFrameInfo::FrameTop)
		|| NowPosition[0] > scaleSize[0] + XCFrameInfo::FrameRight || NowPosition[0] < -(scaleSize[0] + XCFrameInfo::FrameRight)) {
		itemWorkFinish = true;
	}
}
void Item::ItemRelease()
{
	renderHelper->Release();
	delete renderHelper;
}

bool Item::getIsFinish()
{
	return itemWorkFinish;
}

float * Item::getPosition()
{
	return NowPosition;
}

void Item::setPosition(float x, float y, float z)
{
	NowPosition[0] = x;
	NowPosition[1] = y;
	NowPosition[2] = z;
}
