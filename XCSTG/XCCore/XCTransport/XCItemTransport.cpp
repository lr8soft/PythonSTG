#include "XCItemTransport.h"

XCItemTransport::XCItemTransport(PyObject * pitem)
{
	itemPointer = pitem;
}

float * XCItemTransport::getPosition()
{
	PyObject* pos = pyLoader.callObjectMethod(itemPointer, "getPos", NULL);
	static float coord[3];
	PyArg_ParseTuple(pos, "fff", &coord[0], &coord[1], &coord[2]);
	return coord;
}

void XCItemTransport::setPosition(float x, float y, float z)
{
	PyObject* parameter = Py_BuildValue("fff", x, y, z);
	PyObject* pFunc = pyLoader.getAttrib(itemPointer,"setPos");
	PyEval_CallObject(pFunc, parameter);

}
