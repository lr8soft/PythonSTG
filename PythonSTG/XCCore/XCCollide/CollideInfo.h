#pragma once
#ifndef _COLLISIONINFO_H_
#define _COLLISIONINFO_H_
#include "CollideHelper.h"
class CollideInfo {
	static CollideHelper *collideHelperP1;
	static float grazeDistance;
public:
	static void setCollideHelper(CollideHelper* helper);
	static CollideHelper* getCollideHelper();

	static float getGrazeDistance();
};
#endif