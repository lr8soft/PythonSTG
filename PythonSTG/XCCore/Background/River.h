#pragma once
#ifndef _RIVER_H_
#define _RIVER_H_
#include "Background.h"
#include <GL/glcorearb.h>
#include "../XCRender/XCAdvImageHelper.h"
#include <glm/glm.hpp>
class River : public Background {
private:
	XCAdvImageHelper *river_bank , *river_bed, *river_tree, *river_water;
	float renderY = 0.0f, treeY = 0.0f, treeY_offset = 0.5f;
	bool isInit = false;
	void bankRender();
	void bedRender();
	void treeRender();
	void waterRender();
	void coordIncrease(float &count, float offset);
public:
	virtual void BackgroundInit();
	virtual void BackgroundRender();
	virtual void BackgroundRelease();

};
#endif
