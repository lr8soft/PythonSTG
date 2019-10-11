#include "CollideInfo.h"

CollideHelper* CollideInfo::collideHelperP1 = nullptr;
float CollideInfo::grazeDistance = 0.06f;

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

float CollideInfo::getGrazeDistance()
{
	return grazeDistance;
}
