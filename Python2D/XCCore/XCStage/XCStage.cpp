#include "XCStage.h"
#include "../../XCInterpreter/ScriptLoader.h"
#include "../../XCCore/XCRender/XCImageHelper.h"
#include "../../XCCore/XCItem/XCPlayer.h"
#include <GL3/gl3w.h>
GLenum XCStage::parseAlphaFunc(int src)
{
	switch (src)
	{
	case 0:
		return GL_NONE;
	case 1:
		return GL_ONE_MINUS_SRC_ALPHA;
	default:
		return GL_NONE;
	}
}
GLenum XCStage::parseColorFunc(int src)
{
	switch (src)
	{
	case 0:
		return GL_NONE;
	case 1:
		return GL_ONE_MINUS_SRC_COLOR;
	default:
		return GL_NONE;
	}
}
XCStage::XCStage(std::string uuid, PyObject* item)
{
	itemStage = item;
	stageUuid = uuid;
}

void XCStage::stageInit()
{
	if (!getStageInit()) {
		MultiThreadDefine
			
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
					//auto uuidInfo = PyObject_CallMethod(pItem, "_cpp_getUUID", NULL);
					auto initCoordInfo = PyObject_CallMethod(pItem, "_cpp_getInitCoord", NULL);

					const char* imagePath; int divideFormat[4], isFlexible;
					PyArg_ParseTuple(imageInfo, "s(iiii)p", &imagePath, &divideFormat[0], &divideFormat[1], &divideFormat[2], &divideFormat[3], &isFlexible);

					float scaleSize[3];
					PyArg_ParseTuple(scaleInfo, "fff", &scaleSize[0], &scaleSize[1], &scaleSize[2]);

					float rotateAngle; int rotateWork[3];
					PyArg_ParseTuple(rotateInfo, "f(iii)", &rotateAngle, &rotateWork[0], &rotateWork[1], &rotateWork[2]);

					int useBlend, blendColorFunc, blendAlphaFunc;
					PyArg_ParseTuple(blendInfo, "i(ii)", &useBlend, &blendColorFunc, &blendAlphaFunc);

					//const char* uuid;
					//PyArg_Parse(uuidInfo, "s", &uuid);

					float initCoord[3];
					PyArg_ParseTuple(initCoordInfo, "fff", &initCoord[0], &initCoord[1], &initCoord[2]);

					XCImageHelper* image = new XCImageHelper(imagePath, isFlexible);
					XCItem* pItem = new XCItem( image, glm::vec4(divideFormat[0], divideFormat[1], divideFormat[2], divideFormat[3]),
							glm::vec4(1.0f), glm::vec3(scaleSize[0], scaleSize[1], scaleSize[2]), glm::vec3(rotateWork[0], rotateWork[1], rotateWork[2]), rotateAngle);
					pItem->setPosition(initCoord[0], initCoord[1], initCoord[2]);
					pItem->ItemInit();
					itemStruct renderItem;
					renderItem.item = pItem;
					renderItem.useBlend = useBlend;
					renderItem.colorFunc = parseColorFunc(blendColorFunc);
					renderItem.alphaFunc = parseAlphaFunc(blendAlphaFunc);
					stageItemGroup.push_back(renderItem);
#ifdef _DEBUG
					std::cout << "*******stage item*******" << std::endl;
					std::cout << "index: " << i << std::endl;
					std::cout << "path: " << imagePath << " format:" << divideFormat[0] << " " << divideFormat[1] << " " << divideFormat[2] << " " << divideFormat[3] <<" fx:" <<isFlexible << std::endl;
					std::cout << "scale: " << scaleSize[0] << " " << scaleSize[1] << " " << scaleSize[2] << std::endl;
					std::cout << "rotate: " << rotateAngle << " rotatework:" << rotateWork[0] << " " << rotateWork[1] << " " << rotateWork[2] << std::endl;
					std::cout << "useBlend: " << useBlend << " colorFunc:" << blendColorFunc << " alphaFunc:" << blendAlphaFunc << std::endl;
					std::cout << "initCoord: " << initCoord[0] << " " << initCoord[1] << " " << initCoord[2] << std::endl;
					//std::cout << "uuid: " << uuid << std::endl;
					std::cout << "**********************"<< std::endl;
#endif

				}
			}
		}

		MultiThreadDefineEnd
		isStageInit = true;
	}
}

void XCStage::stageWork()
{
	timer.Tick();
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
}

void XCStage::stageRelease()
{
}

bool XCStage::getStageInit()
{
	return isStageInit;
}

bool XCStage::getStageFinish()
{
	return stageFinish;
}

std::string XCStage::getUuid()
{
	return stageUuid;
}
