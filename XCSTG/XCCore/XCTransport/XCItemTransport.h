#pragma once
#ifndef _ITEMTRANSPORT_H_
#define _ITEMTRANSPORT_H_
#include "../../XCInterpreter/ScriptLoader.h"
class XCItemTransport {
private:
	ScriptLoader pyLoader;
	PyObject* itemPointer;
public:
	XCItemTransport(PyObject* pitem);
	float* getPosition();
	void setPosition(float x, float y, float z);
};
#endif