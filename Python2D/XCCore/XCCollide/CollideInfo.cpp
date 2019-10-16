#include "CollideInfo.h"

CollideHelper* CollideInfo::collideHelperP1 = nullptr;
float CollideInfo::grazeDistance = 0.06f;

void CollideInfo::setCollideHelper(CollideHelper * helper)
{
	if (collideHelperP1 == nullptr) {
		collideHelperP1 = helper;
	}
}

CollideHelper * CollideInfo::getCollideHelper()
{
	return collideHelperP1;
}

float CollideInfo::getGrazeDistance()
{
	return grazeDistance;
}
