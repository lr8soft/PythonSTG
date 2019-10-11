#pragma once
#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_
#include <vector>
#include "RenderObject.h"
class RenderManager {
private:
	std::vector<RenderObject*> renderObjectList;

	static RenderManager* pRenderManager;
	RenderManager();
public:
	static RenderManager* getInstance();

	void RenderWork();

	void CleanRenderObject();
	bool CheckRenderComplete();
	void AddRenderObject(RenderObject* object);
};
#endif