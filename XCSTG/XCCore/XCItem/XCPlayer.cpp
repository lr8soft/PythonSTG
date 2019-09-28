#include <GL3/gl3w.h>
#include "XCPlayer.h"
#include "../../XCFrame.h"
#include "../../XCCore/XCRender/XCImageHelper.h"
std::map<std::string, XCPlayer*> XCPlayer::playerInstanceGroup;
void XCPlayer::addPlayerInstance(std::string name, XCPlayer *instance)
{
	playerInstanceGroup.insert(std::make_pair(name, instance));
}
std::map<std::string, XCPlayer*>* XCPlayer::getPlayerGroup()
{
	return &playerInstanceGroup;
}
XCPlayer::XCPlayer(std::string uuid, const char* image, glm::vec4 dInfo, glm::vec4 color, glm::vec3 sSize, glm::vec3 rWork, float rAngle,
	 float mSpeed, float isInterval, float bPower, int sbyRow, int tLeftRow, int tRightRow):XCItem(uuid, nullptr, dInfo, color, sSize, rWork, rAngle)
{
	playerImage = image;

	baseSpeed = mSpeed;
	imageSwapTime = isInterval;
	basePower = bPower;

	standByRow = sbyRow;
	turnLeftRow = tLeftRow;
	turnRightRow = tRightRow;
}
bool XCPlayer::getIsInit()
{
	return isInit;
}
void XCPlayer::ItemInit()
{
	if (!isInit) {
		renderHelper = new XCImageHelper(playerImage, true);
		isInit = true;
	}
}
void XCPlayer::ItemRender()
{
	if (isInit) {
		playerKeyCheck();
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		switch (playerNowState) {
		case PLAYER_STANDBY:
			renderHelper->Render(
				glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]),
				coverColor,
				rotateAngle,
				rotateWork,
				scaleSize,
				IRenderHelper::GetSpecificTexWithRate(
					XCFrame::FrameRight, XCFrame::FrameTop, divideInfo[0], divideInfo[1], 1 + (size_t)playerSameStateTime, standByRow)
			);
			break;
		case PLAYER_TURNRIGHT:
			renderHelper->Render(
				glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]),
				coverColor,
				rotateAngle,
				rotateWork,
				scaleSize,
				IRenderHelper::GetSpecificTexWithRate(
					XCFrame::FrameRight, XCFrame::FrameTop, divideInfo[0], divideInfo[1], 1 + (size_t)playerSameStateTime, turnRightRow)
			);
			break;
		case PLAYER_TURNLEFT:
			renderHelper->Render(
				glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]),
				coverColor,
				rotateAngle,
				rotateWork,
				scaleSize,
				IRenderHelper::GetSpecificTexWithRate(
					XCFrame::FrameRight, XCFrame::FrameTop, divideInfo[0], divideInfo[1], 1 + (size_t)playerSameStateTime, turnLeftRow)
			);
			break;
		}
		glDisable(GL_BLEND);
		itemTimer.Tick();
	}
}

void XCPlayer::playerKeyCheck()
{
	bool have_player_change_state = false;
	auto screen = XCFrame::getInstance()->getScreen();
	if (glfwGetKey(screen, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(screen, true);
	}
	float moveSpeed = baseSpeed * itemTimer.getDeltaFrame(); // adjust accordingly
	if (glfwGetKey(screen, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		moveSpeed = moveSpeed / 1.5f * 0.40f;
		//RenderDecisionPoint = true;
	}
	if (glfwGetKey(screen, GLFW_KEY_UP) == GLFW_PRESS) {
		if (NowPosition[1] + moveSpeed < XCFrame::FrameTop)//·ÀÖ¹Ô½½ç
			NowPosition[1] += moveSpeed * XCFrame::FrameTop;
		setPlayerDirection(PLAYER_STANDBY);
		have_player_change_state = true;
	}

	if (glfwGetKey(screen, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (NowPosition[1] - moveSpeed > XCFrame::FrameBottom)
			NowPosition[1] -= moveSpeed * XCFrame::FrameTop;
		setPlayerDirection(PLAYER_STANDBY);
		have_player_change_state = true;
	}
	if (glfwGetKey(screen, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		if (NowPosition[0] + moveSpeed < XCFrame::FrameRight)
			NowPosition[0] += moveSpeed * XCFrame::FrameRight;
		setPlayerDirection(PLAYER_TURNRIGHT);
		have_player_change_state = true;
	}

	if (glfwGetKey(screen, GLFW_KEY_LEFT) == GLFW_PRESS) {
		if (NowPosition[0] - moveSpeed > XCFrame::FrameLeft)
			NowPosition[0] -= moveSpeed * XCFrame::FrameRight;
		setPlayerDirection(PLAYER_TURNLEFT);
		have_player_change_state = true;
	}

	if (glfwGetKey(screen, GLFW_KEY_Z) == GLFW_PRESS) {
	
	}
	/*if (glfwGetKey(screen, keyitem) == GLFW_PRESS) {
		player_fire_power += 0.1f;
	}*/
	if (!have_player_change_state) {
		if (playerNowState != PLAYER_TURNRIGHT && playerNowState != PLAYER_TURNLEFT)
			setPlayerDirection(playerNowState);
		else
			setPlayerDirection(PLAYER_STANDBY);
	}
}

void XCPlayer::setPlayerDirection(int direction)
{
	playerNowState = direction;
	if (playerNowState == playerLastState) {
		float interval = divideInfo[0] - 0.1f;
		if (playerSameStateTime < interval) {
			playerSameStateTime += imageSwapTime;
		}
		else {
			playerSameStateTime = 0;
		}
	}
}
