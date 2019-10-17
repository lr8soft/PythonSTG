#include "GameMenu.h"
#include "../../XCFrame.h"
#include "../../XCFrameInfo.h"
#include "../../LaunchHelper.h"
#include "../UserInterface/CoverInterface.h"
#include <GL3/gl3w.h>
GameMenu::GameMenu(){
	timer = XCGameTimer(true);
	menuItem.insert(std::make_pair(0, "Start Game"));
	menuItem.insert(std::make_pair(1, "Practice Mode"));
	menuItem.insert(std::make_pair(2, "Game Settings"));
	menuItem.insert(std::make_pair(3, "Exit Game"));
}

void GameMenu::Init()
{
	if (!isInit) {
		fontHelper.FontASCIIInit();
		confirmEffect = AudioHelper::loadWavFromFile("assets/SE/se_ok00.wav");
		cancelEffect = AudioHelper::loadWavFromFile("assets/SE/se_cancel00.wav");
		isInit = true;
	}
}

void GameMenu::Render()
{
	if (isInit) {
		timer.Tick();
		float startX = 0.5f;
		float startY = 0.6f;
		std::map<int, std::string>::iterator itemStart = menuItem.begin();
		std::map<int, std::string>::iterator itemEnd= menuItem.end();
		fontHelper.SetHeightAndWidth(XCFrameInfo::ScreenHeight, XCFrameInfo::ScreenWidth);

		int nowIndex = 0;
		for (auto item = itemStart; item != itemEnd; item++, nowIndex++) {
			if (nowSelectIndex == item->first) {
				fontHelper.FontASCIIRender(item->second,startX - 0.012f *item->second.size(), startY, 1.3f, glm::vec4(1.0f));
			}
			else {
				fontHelper.FontASCIIRender(item->second, startX - 0.012f *item->second.size(), startY, 1.3f, glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
			}
			startY -= 0.11f;
		}
		checkKeyInput();
	}
}

void GameMenu::checkKeyInput()
{
	if (timer.getAccumlateTime() - lastClickTime > 0.16) {
		GLFWwindow* screen = XCFrame::getInstance()->getScreen();
		if (glfwGetKey(screen, XCFrameInfo::keyUp) == GLFW_PRESS) {
			AudioHelper::stopByBuffer(confirmEffect.wavBuffer);
			AudioHelper::playFromBuffer(confirmEffect.wavBuffer);
			if (nowSelectIndex - 1 >= 0) {
				nowSelectIndex--;
			}
			else {
				nowSelectIndex = menuItem.size() - 1;
			}
		}

		if (glfwGetKey(screen, XCFrameInfo::keyDown) == GLFW_PRESS) {
			AudioHelper::stopByBuffer(confirmEffect.wavBuffer);
			AudioHelper::playFromBuffer(confirmEffect.wavBuffer);
			if (nowSelectIndex  < menuItem.size() - 1) {
				nowSelectIndex++;
			}
			else {
				nowSelectIndex = 0;
			}
		}

		if (glfwGetKey(screen, XCFrameInfo::keyShoot) == GLFW_PRESS) {
			AudioHelper::stopByBuffer(confirmEffect.wavBuffer);
			AudioHelper::playFromBuffer(confirmEffect.wavBuffer);
			switch (nowSelectIndex) {
			case 0:
				LaunchHelper::StartGame();
				isWorkFinish = true;
				break;
			case 1:
				LaunchHelper::StartConfigHelper();
				isWorkFinish = true;
				break;
			case 3:
				LaunchHelper::ExitGame();
				isWorkFinish = true;
				break;
			}
		}

		if (glfwGetKey(screen, XCFrameInfo::keyItem) == GLFW_PRESS) {
			AudioHelper::stopByBuffer(cancelEffect.wavBuffer);
			AudioHelper::playFromBuffer(cancelEffect.wavBuffer);
			nowSelectIndex = 3;
		}

		lastClickTime = timer.getAccumlateTime();
	}
}


void GameMenu::Release()
{
	if (isInit) {
		isInit = false;
	}
}
