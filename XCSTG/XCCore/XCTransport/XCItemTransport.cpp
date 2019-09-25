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
		imageHelper = new XCImageHelper(imagePath);
		
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
#ifdef _DEBUG
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
	if (isRenderFlexible) {
		if (imageHelper!=nullptr) {
			int divCol, divRow, divSCol, divSRow;
			float *coord, scaleX, scaleY, scaleZ;
			MultiThreadDefine
			coord = getPosition();
			PyObject* scaleInfo = PyObject_CallMethod(itemPointer, "_cpp_getScaleSize", NULL);
			PyObject* renderInfo = PyObject_CallMethod(itemPointer, "_cpp_getImageDivideFormat", NULL);
			PyArg_ParseTuple(renderInfo, "iiii", &divCol, &divRow, &divSCol, &divSRow);
			PyArg_ParseTuple(scaleInfo, "fff", &scaleX, &scaleY, &scaleZ);
			MultiThreadDefineEnd
			imageHelper->Render(glm::vec3(coord[0], coord[1], coord[2]), glm::vec4(1.0f), glm::vec3(scaleX, scaleY, scaleZ),
				XCImageHelper::GetSpecificTexture(divCol, divRow, divSCol, divSRow));
			
		}
	}
	else {
		if (imageHelper != nullptr) {
			float *coord ,scaleX, scaleY, scaleZ;
			MultiThreadDefine
			coord = getPosition();
			PyObject* scaleInfo = PyObject_CallMethod(itemPointer, "_cpp_getScaleSize", NULL);
			PyArg_ParseTuple(scaleInfo, "fff", &scaleX, &scaleY, &scaleZ);
			MultiThreadDefineEnd
			imageHelper->Render(glm::vec3(coord[0], coord[1], coord[2]), glm::vec4(1.0f), glm::vec3(scaleX, scaleY, scaleZ),
				nullptr);
			
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
