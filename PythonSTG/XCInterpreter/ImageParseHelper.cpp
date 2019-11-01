#include "ImageParseHelper.h"
#include "../XCCore/XCRender/XCImageHelper.h"
ImageInfo ImageParseHelper::parseImageHelperFromObject(PyObject * object)
{
	ImageInfo info;
	if (object != nullptr) {
		PyObject* imageInfo = PyObject_CallMethod(object, "_cpp_getImageInfo", NULL);

		PyArg_ParseTuple(imageInfo, "sf(ii)(ff)(ii)(ff)(ii)(ii)(ii)(iii)", 
			&info.imagePath, &info.swapSpeed, &info.selectX, &info.selectY,
			&info.zoomX, &info.zoomY, &info.divideColumn, &info.divideRow ,&info.offsetX, &info.offsetY,
			&info.specialCol1Start, &info.specialCol1End, &info.specialCol2Start, &info.specialCol2End, &info.specialCol3Start, &info.specialCol3End,
			&info.specialRow1, &info.specialRow2 ,&info.specialRow3);

	}
	return info;
}
