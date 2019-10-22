#include "BackgroundHelper.h"
#include "MagicForest.h"
#include "Lake.h"
Background * BackgroundHelper::getBackgroundByID(int id)
{
	Background *pBackground = nullptr;
	switch (id) {
	case  0:
		pBackground = new LakeBackground; break;
	case 1:
		pBackground = new MagicForest; break;

	default:
		pBackground = new LakeBackground;
	}
	return pBackground;
}