#include "CollideInfo.h"

CollideHelper* CollideInfo::collideHelperP1 = nullptr;

void CollideInfo::setCollideHelperP1(CollideHelper * helper)
{
	if (collideHelperP1 == nullptr) {
		collideHelperP1 = helper;
	}
}

CollideHelper * CollideInfo::getCollideHelperP1()
{
	return collideHelperP1;
}
