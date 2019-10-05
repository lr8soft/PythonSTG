#pragma once
#ifndef _LAKE_H_
#define _LAKE_H_
#include "Background.h"
#include "../../util/GameTimer.h"
#include <GL/glcorearb.h>
#include "../XCRender/XCAdvImageHelper.h"
#include <glm/glm.hpp>
class LakeBackground : public Background {
private:
	XCGameTimer timer;
	XCAdvImageHelper *lake, *leef, *water;
	float renderX = 0.0f, renderY = 0.0f, waterX = 1.0f, waterY = 1.0f;

	glm::vec4 lakeColor = glm::vec4(1.0f, 1.0f,1.0f,1.0f);
	glm::vec4 waterColor = glm::vec4(0.6f, 0.6f, 1.0f, 0.4f);

	bool isInit = false;
	void renderLakeImage();
	void renderWaterImage();
	void renderLeafImage();
public:
	virtual void BackgroundInit() ;
	virtual void BackgroundRender() ;
	virtual void BackgroundRelease() ;

};
#endif