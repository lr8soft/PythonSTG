#include "RenderManager.h"
#include <GL3/gl3w.h>
#include <GLFW/glfw3.h>
#include "../Enemy/EnemyObject.h"
#include "../Bullet/Bullet.h"
#include "../XCCollide/CollideInfo.h"
#include "../UserInterface/GameInfoInterface.h"
#include "../UserInterface/CoverInterface.h"

RenderManager* RenderManager::pRenderManager = nullptr;
RenderManager::RenderManager() {
	auto coverInterface = CoverInterface::getInstance();
	AddUserInterface("coverImage", coverInterface);

	auto infoInterface = GameInfoInterface::getInstance();
	AddUserInterface("gameInfo", infoInterface);
}

RenderManager * RenderManager::getInstance()
{
	if (pRenderManager == nullptr) {
		pRenderManager = new RenderManager;
		if (pRenderManager->getPlayer() == nullptr)
		{
			auto group = Player::getPlayerGroup();
			if (!group->empty()) {
				pRenderManager->setPlayer(group->begin()->second);
			}
		}
	}
	return pRenderManager;
}

void RenderManager::AddRenderObject(std::string parentUuid, RenderObject * object)
{
	renderObjectList.insert(std::make_pair(parentUuid, object));
	object->Init();
	if (parentUuid == StrikeRenderGroupUuid) {
		strikeCollisionHelperGroup.push_back(object);
	}
}

void RenderManager::AddUserInterface(std::string uiName, IUserInterface * ui)
{
	uiGroup.insert(std::make_pair(uiName, ui));
}

void RenderManager::SetBackgroundPointer(Background * bg)
{
	renderBackground = bg;
}

size_t RenderManager::GetRenderObjectCount()
{
	return renderObjectList.size();
}

void RenderManager::RenderWork()
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (renderBackground != nullptr) {
		renderBackground->BackgroundRender();
	}
	if (player != nullptr) {
		if (!player->getIsInit()) {
			player->PlayerInit();
		}
		if (player->getIsInit()) {
			player->PlayerRender();
		}

	}
	std::multimap<std::string, RenderObject*>::iterator renderBegin = renderObjectList.begin();
	std::multimap<std::string, RenderObject*>::iterator renderEnd = renderObjectList.end();
	for (auto object = renderBegin; object != renderEnd; object++) {
		RenderObject *renderObject = object->second;
		if (!renderObject->getIsTerminate()) {
			renderObject->Render();

			if (renderObject->getCurrentType()==RenderObject::BulletType) {
				auto collideHelperP1 = CollideInfo::getCollideHelperP1();
				if (collideHelperP1 != nullptr) {
					collideHelperP1->checkCollisionWithBullet(static_cast<Bullet*>(renderObject));
				}
			}
			else if (renderObject->getCurrentType() == RenderObject::EnemyType) {
			
			}
		}
		if (renderObject->getIsTerminate()) {
			renderObject->Release();
			if (object->first == StrikeRenderGroupUuid) {
				auto iter = std::find(strikeCollisionHelperGroup.begin(), strikeCollisionHelperGroup.end(), renderObject);
				strikeCollisionHelperGroup.erase(iter);
			}

			delete renderObject;
			if (std::next(object) == renderEnd)
			{
				renderObjectList.erase(object);
				break;
			}
			else {
				object = renderObjectList.erase(object);
				renderEnd = renderObjectList.end();
			}
		}
	}

	std::map<std::string, IUserInterface*>::iterator uiBegin = uiGroup.begin();
	std::map<std::string, IUserInterface*>::iterator uiEnd = uiGroup.end();
	for (auto uiIter = uiBegin; uiIter != uiEnd; uiIter++) {
		IUserInterface* ui = uiIter->second;

		if (!ui->getIsInit()) {
			ui->UserInterfaceInit();
		}
		if (ui->getIsInit()) {
			ui->UserInterfaceRender();
			//shouldGamePause = ui->getShouldPauseGame();
		}
		if (ui->getIsWorkFinish()) {
			if (std::next(uiIter) == uiEnd)
			{
				uiGroup.erase(uiIter);
				break;
			}
			else {
				uiGroup.erase(uiIter++);
				uiEnd = uiGroup.end();
			}
		}

	}
}

void RenderManager::CleanRenderObject(std::string uuid)
{
	std::multimap<std::string, RenderObject*>::iterator renderBegin = renderObjectList.find(uuid);
	std::multimap<std::string, RenderObject*>::iterator renderEnd = renderObjectList.end();
	for (auto object = renderBegin; object != renderEnd; object = renderObjectList.find(uuid)) {
		RenderObject *renderObject = object->second;
		renderObject->Release();
		delete renderObject;
		if (std::next(object) == renderEnd)
		{
			renderObjectList.erase(object);
			break;
		}
		else {
			renderObjectList.erase(object++);
			renderEnd = renderObjectList.end();
		}
	}
}

bool RenderManager::CheckRenderComplete(std::string uuid)
{
	return  renderObjectList.find(uuid)== renderObjectList.end();
}

Player * RenderManager::getPlayer()
{
	return player;
}

void RenderManager::setPlayer(Player * p1)
{
	player = p1;
	CollideInfo::setCollideHelper(new CollideHelper(p1));
}
