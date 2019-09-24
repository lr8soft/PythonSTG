#pragma once
#ifndef _RenderManager_H_
#define _RenderManager_H_
#include <vector>
#include <string>
#include <mutex>
#include "IRenderHelper.h"
struct RenderItem {
	std::string renderType;
	std::string imagePath;
	IRenderHelper *image;
	glm::vec3 renderPos;
	glm::vec4  renderColor;
	glm::vec3  scaleSize;
	int divideInfo[4];//col row scol srow
	bool visible = true;
	bool flexible = false;
	bool init = false;
};
class RenderManager {
private:
	static std::mutex renderMutex;
	static std::vector<RenderItem> renderQueue;
	static RenderManager* pRManager;
	RenderManager();
public:
	static RenderManager* getInstance();
	void AddWork(RenderItem work);
	void RenderWork();
};
#endif