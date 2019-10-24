#include "LaunchHelper.h"
#include "XCInterpreter/XCInterpreter.h"
#include "XCCore/Menu/GameMenu.h"
#include "XCCore/Task/TaskManager.h"
#include "XCCore/UserInterface/GameInfoInterface.h"
#include "XCCore/XCRender/RenderManager.h"
#include "XCFrame.h"
void LaunchHelper::StartGame()
{

	/*task manager init*/
	XCInterpreter interperter;
	interperter.getInitInfo();
	interperter.loadTaskManagerInfo();

	auto group = Player::getPlayerGroup();
	if (!group->empty()) {
		RenderManager::getInstance()->setPlayer(group->begin()->second);
	}

	/*render manager init*/
	auto infoInterface = GameInfoInterface::getInstance();
	RenderManager::getInstance()->AddUserInterface(GameInfoUIUuid, infoInterface);

}

void LaunchHelper::StartConfigHelper()
{
	system("PythonSTGConfig.exe");
}

void LaunchHelper::LoadGameMenu()
{
	TaskManager::getInstance()->CleanAllStage();
	RenderManager::getInstance()->CleanAllRenderObject();
	RenderManager::getInstance()->CleanUserInterface(GameInfoUIUuid);
	if (RenderManager::getInstance()->getPlayer()!=nullptr) {
		RenderManager::getInstance()->getPlayer()->PlayerRelease();
		RenderManager::getInstance()->setPlayer(nullptr);
	}

	auto menu = new GameMenu;
	RenderManager::getInstance()->AddRenderObject(MenuUniformUUID, menu, true);
}


void LaunchHelper::ExitGame()
{
	glfwSetWindowShouldClose(XCFrame::getInstance()->getScreen(), true);
}
