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
/* Item Init
PyObject* itemSizeObj = PyObject_CallMethod(itemStage, "_cpp_getItemSize", NULL);
		int itemSize = ScriptLoader::getSingleArg<int>(itemSizeObj);
		if (itemSize > 0) {
			for (int i = 0; i < itemSize; i++) {
				PyObject *pItem, *itemObj = PyObject_CallMethod(itemStage, "_cpp_getItem", NULL);
				PyArg_Parse(itemObj, "O", &pItem);
				if (pItem!=nullptr) {
					auto imageInfo = PyObject_CallMethod(pItem, "_cpp_getInitRenderInfo" ,NULL);
					auto scaleInfo = PyObject_CallMethod(pItem, "_cpp_getScaleSize", NULL);
					auto rotateInfo = PyObject_CallMethod(pItem, "_cpp_getRotateInfo", NULL);
					auto blendInfo = PyObject_CallMethod(pItem, "_cpp_getBlendInfo", NULL);
					auto initCoordInfo = PyObject_CallMethod(pItem, "_cpp_getInitCoord", NULL);

					const char* imagePath; int divideFormat[4], isFlexible;
					PyArg_ParseTuple(imageInfo, "s(iiii)p", &imagePath, &divideFormat[0], &divideFormat[1], &divideFormat[2], &divideFormat[3], &isFlexible);

					float scaleSize[3];
					PyArg_ParseTuple(scaleInfo, "fff", &scaleSize[0], &scaleSize[1], &scaleSize[2]);

					float rotateAngle; int rotateWork[3];
					PyArg_ParseTuple(rotateInfo, "f(iii)", &rotateAngle, &rotateWork[0], &rotateWork[1], &rotateWork[2]);

					int useBlend, blendColorFunc, blendAlphaFunc;
					PyArg_ParseTuple(blendInfo, "i(ii)", &useBlend, &blendColorFunc, &blendAlphaFunc);


					float initCoord[3];
					PyArg_ParseTuple(initCoordInfo, "fff", &initCoord[0], &initCoord[1], &initCoord[2]);

					XCImageHelper* image = new XCImageHelper(imagePath, isFlexible);
					Item* pItem = new Item( image, glm::vec4(divideFormat[0], divideFormat[1], divideFormat[2], divideFormat[3]),
							glm::vec4(1.0f), glm::vec3(scaleSize[0], scaleSize[1], scaleSize[2]), glm::vec3(rotateWork[0], rotateWork[1], rotateWork[2]), rotateAngle);
					pItem->setPosition(initCoord[0], initCoord[1], initCoord[2]);
					pItem->ItemInit();
					itemStruct renderItem;
					renderItem.item = pItem;
					renderItem.useBlend = useBlend;
					renderItem.colorFunc = parseColorFunc(blendColorFunc);
					renderItem.alphaFunc = parseAlphaFunc(blendAlphaFunc);
					stageItemGroup.push_back(renderItem);
				}
			}
		}
*/

/*Item render
	std::vector<itemStruct>::iterator itemBegin = stageItemGroup.begin();
	std::vector<itemStruct>::iterator itemEnd = stageItemGroup.end();
	for (auto item = itemBegin; item != itemEnd; item++) {
		if (!item->item->getIsFinish()) {
			if (item->useBlend) {
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_COLOR, item->colorFunc);
				glBlendFunc(GL_SRC_ALPHA, item->alphaFunc);
			}
			item->item->ItemRender();
			if (item->useBlend) {
				glDisable(GL_BLEND);
			}
		}
		if (item->item->getIsFinish()) {
			item->item->ItemRelease();
			if (std::next(item) == stageItemGroup.end()) {
				stageItemGroup.erase(item);
				break;
			}
			else {
				item = stageItemGroup.erase(item);
				itemEnd = stageItemGroup.end();
			}
		}
	}
*/