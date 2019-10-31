#include "Item.h"
#include "../XCRender/XCImageHelper.h"
#include "../../XCFrameInfo.h"
#include <GL3/gl3w.h>
Item::Item(const glm::vec2& generateCoord, ItemType itemType, float v)
{
	NowPosition = generateCoord;
	currentType = itemType;
	velocity = v;

	divideInfo = glm::vec4();
	divideInfo.x = 4;
	divideInfo.y = 5;
	switch (itemType) {
	case ItemType::PointType:
		divideInfo.z = 2;
		divideInfo.w = 5;
		break;
	case ItemType::BombType:
		divideInfo.z = 2;
		divideInfo.w = 1;
		break;
	case ItemType::PowerType:
		divideInfo.z = 1;
		divideInfo.w = 5;
		break;
	case ItemType::FullPowerType:
		divideInfo.z = 2;
		divideInfo.w = 4;
		break;
	case ItemType::LifeType:
		divideInfo.z = 1;
		divideInfo.w = 2;
		break;
	}
	setCurrentType(ObjectType::ItemType);
}

void Item::Init()
{
	if (!isInit) {
		itemImage = new XCImageHelper("assets/Item/item.png", true);
		isInit = true;
	}
}

void Item::Render()
{
	if (isInit) {
		timer.Tick();
		NowPosition.y -= velocity * timer.getDeltaFrame();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		itemImage->Render(glm::vec3(NowPosition, 0.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0, 0, 1), glm::vec3(0.05f),
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, divideInfo.x, divideInfo.y, divideInfo.z, divideInfo.w));
		glDisable(GL_BLEND);

		if (NowPosition.y - 0.05f< -1.0f ) {
			isWorkFinish = true;
		}
	}
}

void Item::Release()
{
	if (isInit) {
		itemImage->Release();
		delete itemImage;

		isInit = false;
	}
}
