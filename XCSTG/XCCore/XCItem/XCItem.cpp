#include "XCItem.h"
#include "../../XCFrame.h"
XCItem::XCItem(std::string uuid, IRenderHelper* image, glm::vec4 dInfo, glm::vec4 color, glm::vec3 sSize, glm::vec3 rWork, float rAngle)
{
	renderHelper = image;
	divideInfo = dInfo;
	scaleSize = sSize;
	rotateWork = rWork;
	rotateAngle = rAngle;
	coverColor = color;
	itemUuid = uuid;
}

void XCItem::ItemInit()
{
}

void XCItem::ItemRender()
{
	if (renderHelper != nullptr) {
		itemTimer.Tick();
		renderHelper->Render(
			glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]),
			coverColor,
			rotateAngle,
			rotateWork,
			scaleSize,
			IRenderHelper::GetSpecificTexWithRate(
				XCFrame::FrameRight,XCFrame::FrameTop,divideInfo[0], divideInfo[1], divideInfo[2], divideInfo[3])
		);
	}
}

void XCItem::ItemRelease()
{
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

std::string XCItem::getUuid()
{
	return itemUuid;
}
