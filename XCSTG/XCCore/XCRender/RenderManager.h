#pragma once
#ifndef _RenderManager_H_
#define _RenderManager_H_
#include <vector>
#include <string>
#include <mutex>
#include "IRenderHelper.h"
#include "../XCTransport/XCItemTransport.h"
struct StaticRenderItem {
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
struct DynamicRenderItem {
	XCItemTransport *item;
};
class RenderManager {
private:
	static std::mutex staticMutex, dynamicMutex;
	static std::vector<DynamicRenderItem> dynamicRenderGroup;
	static std::vector<StaticRenderItem> staticQueue;

	static RenderManager* pRManager;
	RenderManager();
public:
	static RenderManager* getInstance();
	void AddDynamicWork(DynamicRenderItem work);
	void AddStaticWork(StaticRenderItem work);
	void RenderWork();
};
#endif