#pragma once
#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_
#include <map>
#include <string>
#include "RenderObject.h"
class RenderManager {
private:
	std::multimap<std::string, RenderObject*> renderObjectList;

	static RenderManager* pRenderManager;
	RenderManager();
public:
	static RenderManager* getInstance();

	void RenderWork();

	void CleanRenderObject(std::string parentUuid);
	bool CheckRenderComplete(std::string parentUuid);
	void AddRenderObject(std::string parentUuid,RenderObject* object);
};
#endif