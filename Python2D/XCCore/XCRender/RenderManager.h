#pragma once
#ifndef _RenderManager_H_
#define _RenderManager_H_
#include <vector>
#include <string>
#include <mutex>
#include "IRenderHelper.h"
#include "../Stage/Stage.h"
#include "../Item/Player.h"
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
	std::vector<Stage*> stageQueue;
	std::vector<StaticRenderItem> staticQueue;
	Player* playerP1;

	static RenderManager* pRManager;
	RenderManager();
public:
	static RenderManager* getInstance();
	void AddStaticWork(StaticRenderItem work);
	void AddStageItem(Stage* stage);
	void RenderWork();

	Player* getPlayerP1();
	void setPlayerP1(Player* p1);
};
#endif