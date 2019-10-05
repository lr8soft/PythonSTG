#include "BackgroundHelper.h"
#include "Lake.h"
Background * BackgroundHelper::getBackgroundByID(int id)
{
	Background *pBackground = nullptr;
	switch (id) {
	case  0:
		pBackground = new LakeBackground; break;



	default:
		pBackground = new LakeBackground;
	}
	return pBackground;
}
