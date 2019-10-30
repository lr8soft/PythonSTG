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
	float renderX = 0.0f, renderY = 0.0f, renderX1 = 0.0f, renderX2 = 0.5f;
	bool isInit = false;
	void bankRender();
	void bedRender();
	void treeRender();
	void waterRender();
public:
	virtual void BackgroundInit();
	virtual void BackgroundRender();
	virtual void BackgroundRelease();

};
#endif
