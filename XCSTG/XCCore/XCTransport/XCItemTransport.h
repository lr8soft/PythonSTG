#pragma once
#ifndef _ITEMTRANSPORT_H_
#define _ITEMTRANSPORT_H_
#include "../XCRender/XCImageHelper.h"
#include <Python.h>
class XCItemTransport {
private:
	bool isInit = false;
	bool isRenderFlexible = false;
	PyObject* itemPointer;
	XCImageHelper* imageHelper;
	int divideInfo[4] = {0, 0, 0, 0};
public:
	XCItemTransport(PyObject* pitem);
	bool getIsInit();
	bool getRemoval();
	void ItemInit();
	void ItemRender();
	std::string getUuid();
	float* getPosition();
	void setPosition(float x, float y, float z);
	void Finalizer();
	
};
#endif