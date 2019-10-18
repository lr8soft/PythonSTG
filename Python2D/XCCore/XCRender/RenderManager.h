#pragma once
#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_
#include <list>
#include <string>
#include <unordered_map>
#include "../UserInterface/IUserInterface.h"
#include "../Background/Background.h"
#include "../Item/Player.h"
#include "RenderObject.h"

#define StrikeRenderGroupUuid "StrikeGroupUniformUUID"
#define ParticleGroupUuid "ParticleGroupUniformUUID"
class RenderManager {
private:
	enum insideCommand {
		cRenderObject = 0, cAllRenderObject, tBullet, cUserInterface
	};
	std::unordered_multimap<std::string, RenderObject*> renderObjectList;
	std::unordered_multimap<insideCommand, std::string> externCommandList;
	std::unordered_multimap<std::string, RenderObject*> asyncRenderObjectList;

	std::map<std::string, IUserInterface*> uiGroup;
	std::list<RenderObject*> strikeCollisionHelperGroup;

	Background *renderBackground = nullptr;
	Player* player;

	static RenderManager* pRenderManager;
	RenderManager();

	void solveAsyncCommand();
	void solveAsyncObject();
public:
	static RenderManager* getInstance();

	void RenderWork();

	void CleanRenderObject(const std::string& parentUuid);
	void CleanAllRenderObject();
	void CleanUserInterface(const std::string& uuid);
	void TerminateBullet(const std::string& parentUuid);
	bool CheckRenderComplete(const std::string& parentUuid);

	void AddRenderObject(const std::string& parentUuid,RenderObject* object, bool isAsynico = false);
	void AddUserInterface(const std::string& uiName, IUserInterface* ui);

	void SetBackgroundPointer(Background* background);

	size_t GetRenderObjectCount();

	Player* getPlayer();
	void setPlayer(Player* player);
};
#endif