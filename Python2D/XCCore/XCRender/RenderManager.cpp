#include "RenderManager.h"
#include "../../XCFrame.h"
#include <GL3/gl3w.h>
#include <GLFW/glfw3.h>
#include "../Enemy/EnemyObject.h"
#include "../Bullet/Bullet.h"
#include "../Attack/IAttack.h"
#include "../XCCollide/CollideInfo.h"
#include "../UserInterface/GameInfoInterface.h"
#include "../UserInterface/CoverInterface.h"
#include "../Menu/GameMenu.h"
RenderManager* RenderManager::pRenderManager = nullptr;
RenderManager::RenderManager() {
	auto coverInterface = CoverInterface::getInstance();
	AddUserInterface("coverImage", coverInterface);

}


RenderManager * RenderManager::getInstance()
{
	if (pRenderManager == nullptr) {
		pRenderManager = new RenderManager;
	}
	return pRenderManager;
}

void RenderManager::AddRenderObject(const std::string& parentUuid, RenderObject * object, bool isAsyncio)
{
	if (!isAsyncio) {
		renderObjectList.insert(std::make_pair(parentUuid, object));
		object->Init();
		if (parentUuid == StrikeRenderGroupUuid) {
			strikeCollisionHelperGroup.push_back(object);
		}
	}
	else {
		object->Init();
		asyncRenderObjectList.insert(std::make_pair(parentUuid, object));
	}
}

void RenderManager::AddUserInterface(const std::string& uiName, IUserInterface * ui)
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
	std::unordered_multimap<std::string, RenderObject*>::iterator renderBegin = renderObjectList.begin();
	std::unordered_multimap<std::string, RenderObject*>::iterator renderEnd = renderObjectList.end();
	for (auto object = renderBegin; object != renderEnd; object++) {
		RenderObject *renderObject = object->second;
		if (!renderObject->getIsTerminate()) {
			renderObject->Render();
			if (renderObject->getCurrentType()==RenderObject::BulletType) {
				auto collideHelperP1 = CollideInfo::getCollideHelper();
				if (collideHelperP1 != nullptr) {
					collideHelperP1->checkCollisionWithBullet(static_cast<Bullet*>(renderObject));
				}
			}
			else if (renderObject->getCurrentType() == RenderObject::EnemyType && !strikeCollisionHelperGroup.empty()) {
				std::list<RenderObject*>::iterator strikeBegin = strikeCollisionHelperGroup.begin();
				std::list<RenderObject*>::iterator strikeEnd = strikeCollisionHelperGroup.end();
				for (auto strike = strikeBegin; strike != strikeEnd; strike++) {
					IAttack* pStrike = static_cast<IAttack*>(*strike);
					pStrike->checkCollisonWithEnemy(static_cast<EnemyObject*>(renderObject));
				}
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
		}
		if (ui->getIsWorkFinish()) {
			ui->UserInterfaceRelease();
			delete ui;
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
	solveAsyncCommand();
	solveAsyncObject();
}


void RenderManager::solveAsyncCommand()
{
	if (externCommandList.empty()) return;
	std::unordered_multimap<insideCommand, std::string>::iterator commandBegin = externCommandList.begin();
	std::unordered_multimap<insideCommand, std::string>::iterator commandEnd = externCommandList.end();
	for (auto command = commandBegin; command != commandEnd; command++) {
		const insideCommand& info = command->first;
		std::string& uuid = command->second;		

		switch (info)
		{
		case RenderManager::cRenderObject:
			{
				std::unordered_multimap<std::string, RenderObject*>::iterator targetBegin = renderObjectList.find(uuid);
				std::unordered_multimap<std::string, RenderObject*>::iterator targetEnd = renderObjectList.end();
				for (auto object = targetBegin; object != targetEnd; object = renderObjectList.find(uuid)) {
					RenderObject *renderObject = object->second;
					renderObject->Release();
					delete renderObject;
					if (std::next(object) == targetEnd)
					{
						renderObjectList.erase(object);
						break;
					}
					else {
						renderObjectList.erase(object++);
						targetEnd = renderObjectList.end();
					}
				}
			}
			break;
		case RenderManager::cAllRenderObject:
			{
				std::unordered_multimap<std::string, RenderObject*>::iterator renderBegin = renderObjectList.begin();
				std::unordered_multimap<std::string, RenderObject*>::iterator renderEnd = renderObjectList.end();
				for (auto object = renderBegin; object != renderEnd; object++) {
					RenderObject *renderObject = object->second;
					renderObject->Release();
					delete renderObject;
				}
				renderObjectList.clear();
				strikeCollisionHelperGroup.clear();		
			}
			break;
		case RenderManager::tBullet:
			{
				std::unordered_multimap<std::string, RenderObject*>::iterator bulletBegin = renderObjectList.begin();
				std::unordered_multimap<std::string, RenderObject*>::iterator bulletEnd = renderObjectList.end();
				for (auto object = bulletBegin; object != bulletEnd; object++) {
					if (object->first == uuid) {
						RenderObject *renderObject = object->second;
						if (renderObject->getCurrentType() == RenderObject::BulletType) {
							Bullet* pBullet = static_cast<Bullet*>(renderObject);
							pBullet->setBulletTerminate();
						}
					}
				}		
			}
			break;
		default:
			break;
		}
	}
	externCommandList.clear();
}

void RenderManager::solveAsyncObject()
{
	if (asyncRenderObjectList.empty()) return;
	std::unordered_multimap<std::string, RenderObject*>::iterator obegin = asyncRenderObjectList.begin();
	std::unordered_multimap<std::string, RenderObject*>::iterator oend = asyncRenderObjectList.end();

	for (auto object = obegin; object != oend; object++) {
		renderObjectList.insert(std::make_pair(object->first, object->second));
		if (object->first == StrikeRenderGroupUuid) {
			strikeCollisionHelperGroup.push_back(object->second);
		}
	}
	asyncRenderObjectList.clear();
}

void RenderManager::CleanRenderObject(const std::string& uuid)
{
	externCommandList.insert(std::make_pair(RenderManager::cRenderObject, uuid));
}

void RenderManager::CleanAllRenderObject()
{
	externCommandList.insert(std::make_pair(RenderManager::cAllRenderObject, ""));
	
}

void RenderManager::CleanUserInterface(const std::string & uuid)
{
	auto item = uiGroup.find(uuid);
	if (item!=uiGroup.end()) {
		uiGroup.erase(item);
	}
}

void RenderManager::TerminateBullet(const std::string& parentUuid)
{
	externCommandList.insert(std::make_pair(RenderManager::tBullet, parentUuid));
}

bool RenderManager::CheckRenderComplete(const std::string& uuid)
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
