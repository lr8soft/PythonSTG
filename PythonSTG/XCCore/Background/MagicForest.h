#pragma once
#ifndef _MAGIC_FOREST_H_
#define _MAGIC_FOREST_H_
#include "Background.h"
#include <GL/glcorearb.h>
#include "../XCRender/XCAdvImageHelper.h"
#include "Camera.h"
class MagicForest : public Background {
private:
	Camera camera;
	XCAdvImageHelper *ground, *mask;
	float renderX = 0.0f, renderY = 0.0f, waterX = 1.0f, waterY = 1.0f;
	


	glm::vec4 lakeColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 waterColor = glm::vec4(0.37f, 1.0f, 1.0f, 0.65f);

	bool isInit = false;
	void renderGroundImage();
	void renderMaskImage();
public:
	virtual void BackgroundInit();
	virtual void BackgroundRender();
	virtual void BackgroundRelease();

};
#endif