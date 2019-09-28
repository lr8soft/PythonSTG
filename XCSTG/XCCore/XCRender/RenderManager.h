#pragma once
#ifndef _RenderManager_H_
#define _RenderManager_H_
#include <vector>
#include <string>
#include <mutex>
#include "IRenderHelper.h"
#include "../XCStage/XCStage.h"
#include "../XCItem/XCPlayer.h"
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
class RenderManager {
private:
	std::vector<XCStage*> stageQueue;
	std::vector<StaticRenderItem> staticQueue;
	XCPlayer* playerP1;

	static RenderManager* pRManager;
	RenderManager();
public:
	static RenderManager* getInstance();
	void AddStaticWork(StaticRenderItem work);
	void AddStageItem(XCStage* stage);
	void RenderWork();

	XCPlayer* getPlayerP1();
	void setPlayerP1(XCPlayer* p1);
};
#endif