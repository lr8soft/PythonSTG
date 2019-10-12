#pragma once
#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_
#include <map>
#include <string>
#include "../UserInterface/IUserInterface.h"
#include "../Background/Background.h"
#include "../Item/Player.h"
#include "RenderObject.h"
class RenderManager {
private:
	std::multimap<std::string, RenderObject*> renderObjectList;
	std::map<std::string, IUserInterface*> uiGroup;

	bool shouldGamePause = false;
	Background *renderBackground = nullptr;
	Player* player;

	static RenderManager* pRenderManager;
	RenderManager();
public:
	static RenderManager* getInstance();

	void RenderWork();

	void CleanRenderObject(std::string parentUuid);
	bool CheckRenderComplete(std::string parentUuid);

	void AddRenderObject(std::string parentUuid,RenderObject* object);
	void AddUserInterface(std::string uiName, IUserInterface* ui);

	void SetBackgroundPointer(Background* background);

	Player* getPlayer();
	void setPlayer(Player* player);
};
#endif