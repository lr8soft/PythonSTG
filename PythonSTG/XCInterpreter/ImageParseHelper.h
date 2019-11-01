#pragma once
#ifndef _IMAGE_PARSE_HELPER_H_
#define _IMAGE_PARSE_HELPER_H_
#include <Python.h>
#include "../XCCore/XCRender/IRenderHelper.h"
struct ImageInfo {
	const char* imagePath;
	float swapSpeed;
	float zoomX, zoomY, offsetX, offsetY;
	int selectX, selectY;
	int divideColumn, divideRow;
	int specialCol1Start, specialCol1End;
	int specialCol2Start, specialCol2End;
	int specialCol3Start, specialCol3End;
	int specialRow1, specialRow2, specialRow3;

};
class ImageParseHelper {
public:
	static ImageInfo parseImageHelperFromObject(PyObject* object);

};
#endif