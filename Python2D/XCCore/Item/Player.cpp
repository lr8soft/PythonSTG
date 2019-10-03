#include <GL3/gl3w.h>
#include "Player.h"
#include "../../XCFrameInfo.h"
#include "../../XCFrame.h"
#include "../../XCCore/XCRender/XCImageHelper.h"
#include <GLFW/glfw3.h>
std::map<std::string, Player*> Player::playerInstanceGroup;
void Player::addPlayerInstance(std::string name, Player *instance)
{
	playerInstanceGroup.insert(std::make_pair(name, instance));
}
std::map<std::string, Player*>* Player::getPlayerGroup()
{
	return &playerInstanceGroup;
}
Player::Player( const char* image, glm::vec4 dInfo, glm::vec4 color, glm::vec3 sSize, glm::vec3 rWork, float rAngle,
	 float mSpeed, float isInterval, float bPower, int sbyRow, int tLeftRow, int tRightRow):Item(nullptr, dInfo, color, sSize, rWork, rAngle)
{
	playerImage = image;

	baseSpeed = mSpeed;
	imageSwapTime = isInterval;
	basePower = bPower;

	standByRow = sbyRow;
	turnLeftRow = tLeftRow;
	turnRightRow = tRightRow;
}
bool Player::getIsInit()
{
	return isInit;
}
void Player::ItemInit()
{
	if (!isInit) {
		renderHelper = new XCImageHelper(playerImage, true);
		specialEffectDecision = new DecisionPointSpecialEffect;
		specialEffectDecision->SpecialEffectInit();
		isInit = true;
	}
}
void Player::ItemRender()
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
					XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, divideInfo[0], divideInfo[1], 1 + (size_t)playerSameStateTime, standByRow)
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
					XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, divideInfo[0], divideInfo[1], 1 + (size_t)playerSameStateTime, turnRightRow)
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
					XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, divideInfo[0], divideInfo[1], 1 + (size_t)playerSameStateTime, turnLeftRow)
			);
			break;
		}
		glDisable(GL_BLEND);
		if (renderDecisionPoint) {
			specialEffectDecision->SpecialEffectRender(NowPosition[0], NowPosition[1], NowPosition[2]);
		}
		itemTimer.Tick();
	}
}

void Player::ItemRelease()
{
	renderHelper->Release();
	specialEffectDecision->SpecialEffectRelease();
	delete renderHelper, specialEffectDecision;
	isInit = false;
}

void Player::playerKeyCheck()
{
	renderDecisionPoint = false;
	bool have_player_change_state = false;
	auto screen = XCFrame::getInstance()->getScreen();

	float renderX = NowPosition[0] * XCFrameInfo::FrameRight;
	float renderY = NowPosition[1] * XCFrameInfo::FrameTop;
	if (glfwGetKey(screen, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(screen, true);
	}
	float moveSpeed = baseSpeed * itemTimer.getDeltaFrame();
	if (glfwGetKey(screen, XCFrameInfo::p1_keySlow) == GLFW_PRESS) {
		moveSpeed = moveSpeed / 1.5f * 0.40f;
		//have_player_change_state = false;
		renderDecisionPoint = true;
	}
	if (glfwGetKey(screen, XCFrameInfo::p1_keyUp) == GLFW_PRESS) {
		if ( (NowPosition[1] + moveSpeed)*XCFrameInfo::FrameTop < XCFrameInfo::FrameTop)//��ֹԽ��
			NowPosition[1] += moveSpeed;
		setPlayerDirection(PLAYER_STANDBY);
		have_player_change_state = true;
	}

	if (glfwGetKey(screen, XCFrameInfo::p1_keyDown) == GLFW_PRESS) {
		if ( (NowPosition[1] - moveSpeed)*XCFrameInfo::FrameTop > XCFrameInfo::FrameBottom)
			NowPosition[1] -= moveSpeed;
		setPlayerDirection(PLAYER_STANDBY);
		have_player_change_state = true;
	}
	if (glfwGetKey(screen, XCFrameInfo::p1_keyRight) == GLFW_PRESS) {
		if ( (NowPosition[0] + moveSpeed)*XCFrameInfo::FrameRight < XCFrameInfo::FrameRight)
			NowPosition[0] += moveSpeed;
		setPlayerDirection(PLAYER_TURNRIGHT);
		have_player_change_state = true;
	}

	if (glfwGetKey(screen, XCFrameInfo::p1_keyLeft) == GLFW_PRESS) {
		if ( (NowPosition[0] - moveSpeed)*XCFrameInfo::FrameRight > XCFrameInfo::FrameLeft)
			NowPosition[0] -= moveSpeed;
		setPlayerDirection(PLAYER_TURNLEFT);
		have_player_change_state = true;
	}

	if (glfwGetKey(screen, XCFrameInfo::p1_keyShoot) == GLFW_PRESS) {
	
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

void Player::setPlayerDirection(int direction)
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