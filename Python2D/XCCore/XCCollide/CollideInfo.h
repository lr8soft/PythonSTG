#pragma once
#ifndef _COLLISIONINFO_H_
#define _COLLISIONINFO_H_
#include "CollideHelper.h"
class CollideInfo {
	static CollideHelper *collideHelperP1;
	static float grazeDistance;
public:
	static void setCollideHelper(CollideHelper* helper);
	static CollideHelper* getCollideHelperP1();

	static float getGrazeDistance();
};
#endif