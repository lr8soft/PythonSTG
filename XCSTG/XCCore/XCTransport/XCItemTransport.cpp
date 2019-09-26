#include "XCItemTransport.h"
#include <iostream>
#include "../../XCInterpreter/ScriptLoader.h"

#include <GL3/gl3w.h>
XCItemTransport::XCItemTransport(PyObject * pitem)
{
	itemPointer = pitem;
}

bool XCItemTransport::getIsInit()
{
	return isInit;
}

bool XCItemTransport::getRemoval()
{
	return false;
}

void XCItemTransport::ItemInit()
{
	
	if (!isInit) {
		const char* imagePath;
		int isFlexible;
		PyObject* initInfo;
		{
			MultiThreadDefine
			initInfo = PyObject_CallMethod(itemPointer, "_cpp_getInitRenderInfo", NULL);
			PyArg_ParseTuple(
				initInfo, "s(iiii)p",
				&imagePath, &divideInfo[0], &divideInfo[1], &divideInfo[2], &divideInfo[3], &isFlexible
			);
			MultiThreadDefineEnd
		}
		isRenderFlexible = isFlexible ? true : false;
		imageHelper = new XCImageHelper(imagePath, isRenderFlexible);
		
#ifdef _DEBUG
		std::cout << "=======DYNAMIC RENDER ITEM=====" << std::endl;
		std::cout << "Image path:" << imagePath <<" IsFlexible: "<< std::boolalpha <<isRenderFlexible << std::endl;
		std::cout << "Divide type:" << divideInfo[0] << " " << divideInfo[1] << " " << divideInfo[2] << " "<< divideInfo[3] << std::endl;
		std::cout << "==============================" << std::endl;
#endif
		isInit = true;
	}
	
	
}

void XCItemTransport::ItemRender()
{
//Just for test
	if (isRenderFlexible) {
		if (imageHelper!=nullptr) {
			int divCol, divRow, divSCol, divSRow, rotateWorkX, rotateWorkY, rotateWorkZ;
			int useBlend, colorFunc, alphaFunc;
			float *coord, scaleX, scaleY, scaleZ, rotateAngle;
			MultiThreadDefine
			coord = getPosition();
			PyObject* scaleInfo = PyObject_CallMethod(itemPointer, "_cpp_getScaleSize", NULL);
			PyObject* renderInfo = PyObject_CallMethod(itemPointer, "_cpp_getImageDivideFormat", NULL);
			PyObject* rotateInfo = PyObject_CallMethod(itemPointer, "_cpp_getRotateInfo", NULL);
			PyObject* blendInfo = PyObject_CallMethod(itemPointer, "_cpp_getBlendInfo", NULL);
			PyArg_ParseTuple(renderInfo, "iiii", &divCol, &divRow, &divSCol, &divSRow);
			PyArg_ParseTuple(scaleInfo, "fff", &scaleX, &scaleY, &scaleZ);
			PyArg_ParseTuple(rotateInfo, "f(iii)",&rotateAngle, &rotateWorkX, &rotateWorkY, &rotateWorkZ);
			PyArg_ParseTuple(blendInfo, "p(ii)", &useBlend, &colorFunc,&alphaFunc);
			MultiThreadDefineEnd
				
			if (useBlend) {
				glEnable(GL_BLEND);
				switch (alphaFunc) {
				case 4:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
				case 5:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
				}
				switch (colorFunc) {
				case 1:
					glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR); break;
				case 2:
					glBlendFunc(GL_SRC_COLOR, GL_ONE); break;
				}
			}
			imageHelper->Render(glm::vec3(coord[0], coord[1], coord[2]), glm::vec4(1.0f), 
				rotateAngle, glm::vec3(rotateWorkX, rotateWorkY, rotateWorkZ),glm::vec3(scaleX, scaleY, scaleZ),
				XCImageHelper::GetSpecificTexture(divCol, divRow, divSCol, divSRow));
			if (useBlend) {
				glDisable(GL_BLEND);
			}
		}
	}
	else {
		if (imageHelper != nullptr) {
			float *coord ,scaleX, scaleY, scaleZ, rotateAngle;
			int  rotateWorkX, rotateWorkY, rotateWorkZ;
			int useBlend, colorFunc, alphaFunc;
			MultiThreadDefine
			coord = getPosition();
			PyObject* scaleInfo = PyObject_CallMethod(itemPointer, "_cpp_getScaleSize", NULL);
			PyObject* rotateInfo = PyObject_CallMethod(itemPointer, "_cpp_getRotateInfo", NULL);
			PyObject* blendInfo = PyObject_CallMethod(itemPointer, "_cpp_getBlendInfo", NULL);
			PyArg_ParseTuple(scaleInfo, "fff", &scaleX, &scaleY, &scaleZ);
			PyArg_ParseTuple(rotateInfo, "f(iii)", &rotateAngle, &rotateWorkX, &rotateWorkY, &rotateWorkZ);
			PyArg_ParseTuple(blendInfo, "p(ii)", &useBlend, &colorFunc, &alphaFunc);
			MultiThreadDefineEnd
			if (useBlend) {
				glEnable(GL_BLEND);
				switch (alphaFunc) {
				case 4:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
				case 5:
					glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
				}
				switch (colorFunc) {
				case 1:
					glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR); break;
				case 2:
					glBlendFunc(GL_SRC_COLOR, GL_ONE); break;
				}
			}
			imageHelper->Render(glm::vec3(coord[0], coord[1], coord[2]), glm::vec4(1.0f), 
				rotateAngle, glm::vec3(rotateWorkX, rotateWorkY, rotateWorkZ), glm::vec3(scaleX, scaleY, scaleZ),
				nullptr);
			if (useBlend) {
				glDisable(GL_BLEND);
			}
		}
	}
	
}

float * XCItemTransport::getPosition()
{
	static float coord[3];
	PyObject* pos = PyObject_CallMethod(itemPointer, "getPos", NULL);
	PyArg_ParseTuple(pos, "fff", &coord[0], &coord[1], &coord[2]);
	return coord;
}

void XCItemTransport::setPosition(float x, float y, float z)
{
	//PyObject* parameter = Py_BuildValue("fff", x, y, z);
	//PyObject* pFunc = pyLoader.getAttrib(itemPointer,"setPos");
	//PyEval_CallObject(pFunc, parameter);
	PyObject_CallMethod(itemPointer, "setPos", "(fff)", x, y, z);
}

void XCItemTransport::Finalizer()
{
	isInit = false;
	delete imageHelper;
#ifndef _DEBUG
	Py_DECREF(itemPointer);
#endif
}

std::string XCItemTransport::getUuid()
{
	const char* uuidTemp;
	std::string uuid;
	auto uuidObj = PyObject_CallMethod(itemPointer, "_cpp_getUUID", NULL);
	PyArg_Parse(uuidObj, "s", &uuidTemp);

	uuid = uuidTemp;
	return uuid;
}
