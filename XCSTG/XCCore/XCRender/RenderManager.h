#pragma once
#ifndef _RenderManager_H_
#define _RenderManager_H_
#include <vector>
#include <string>
#include "XCImageManager.h"
struct RenderItem {
	std::string renderType;
	std::string imagePath;
	XCImageManager *image;
	glm::vec4 renderPos;
	glm::vec4  renderColor;
	glm::vec3  scaleSize;
	int divideInfo[4];//col row scol srow
	bool visible = true;
};
class RenderManager {
private:
	static std::vector<RenderItem> renderQueue;
	static RenderManager* pRManager;
	RenderManager();
public:
	RenderManager* getInstance();
	void AddWork(RenderItem work);
	void RenderWork();
};
#endif