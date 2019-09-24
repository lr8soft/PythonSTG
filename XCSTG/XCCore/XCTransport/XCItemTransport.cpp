#include "XCItemTransport.h"

XCItemTransport::XCItemTransport(PyObject * pitem)
{
	itemPointer = pitem;
}

float * XCItemTransport::getPosition()
{
	return nullptr;
}

void XCItemTransport::setPosition(float x, float y, float z)
{
}
