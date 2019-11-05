#include <GL3/gl3w.h>
#include "Player.h"
#include "../../XCFrameInfo.h"
#include "../../XCFrame.h"
#include "../XCRender/RenderManager.h"
#include "../../XCCore/XCRender/XCImageHelper.h"
#include "../XCRender/ParticleHelper.h"
#include "../Attack/NormalStrike.h"
#include "../UserInterface/GameInfoInterface.h"
#include "../../LaunchHelper.h"
std::map<std::string, Player*> Player::playerInstanceGroup;
void Player::addPlayerInstance(std::string name, Player *instance)
{
	playerInstanceGroup.insert(std::make_pair(name, instance));
}
std::map<std::string, Player*>* Player::getPlayerGroup()
{
	return &playerInstanceGroup;
}
Player::Player( const char* image, glm::vec4 dInfo, glm::vec4 color, glm::vec3 sSize, glm::vec3 rWork, float rAngle,float mSpeed, float isInterval,
	float bPower, int sbyRow, int tLeftRow, int tRightRow)
{
	divideInfo = dInfo;
	scaleSize = sSize;
	rotateWork = rWork;
	rotateAngle = rAngle;
	coverColor = color;
	tempColor = color;

	playerImage = image;

	baseSpeed = mSpeed;
	imageSwapTime = isInterval;
	basePower = bPower;

	standByRow = sbyRow;
	turnLeftRow = tLeftRow;
	turnRightRow = tRightRow;

	GameInfoInterface::setMaxLife(maxLife);
	GameInfoInterface::setNowLife(nowLife);
	GameInfoInterface::setMaxBomb(maxBomb);
	GameInfoInterface::setNowBomb(nowBomb);
}
bool Player::getIsInit()
{
	return isInit;
}
void Player::PlayerInit()
{
	if (!isInit) {
		renderHelper = new XCImageHelper(playerImage, true);
		moonEffectHelper = new XCImageHelper("assets/UI/specialeffect.png", true);

		specialEffectDecision = new DecisionPointSpecialEffect;
		specialEffectDecision->SpecialEffectInit();


		playerHurtAudio = AudioHelper::loadWavFromFile("assets/SE/se_pldead00.wav");
		playerGrazeAudio = AudioHelper::loadWavFromFile("assets/SE/se_graze.wav");
		playerExtentAudio = AudioHelper::loadWavFromFile("assets/SE/se_extend.wav");

		isInit = true;
	}
}
void Player::PlayerRender()
{
	if (isInit) {
		playerKeyCheck();
		itemTimer.Tick();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (isHitTime) {
			coverColor = glm::vec4(1.0f,1.0f,1.0f,0.5f);
		}
		else {
			coverColor = tempColor;
		}
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
		//////////test

		if (isHitTime) {
			if (itemTimer.getAccumlateTime() - lastHitTime > HitProtectTime) {
				isHitTime = false;
			}
		}

		if (isMoonState) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			moonEffectHelper->Render(glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]),glm::vec4(1.0f),
				glm::radians(itemTimer.getAccumlateTime() * 45.0f), glm::vec3(0, 0, 1), glm::vec3(0.25f * XCFrameInfo::FrameRight, 0.25f * XCFrameInfo::FrameTop, 0.25f),
				IRenderHelper::GetSpecificTexture(1, 1, 1, 1));
			glDisable(GL_BLEND);
			if (moonPoint - 1 > 0) {
				moonPoint--;
			}
			else {
				if (moonLevel > 0) {
					moonLevel--;
					moonPoint = maxMoonPoint;
				}
				else {
					isMoonState = false;
				}
			}
		}
		GameInfoInterface::getInstance()->setNowScore(playerScore);
		///////////test
	}
}

void Player::PlayerRelease()
{
	renderHelper->Release();
	specialEffectDecision->SpecialEffectRelease();
	moonEffectHelper->Release();
	delete renderHelper, specialEffectDecision, moonEffectHelper;
	isInit = false;
}

float * Player::getPosition()
{
	return NowPosition;
}

void Player::hurtPlayer()
{
	if (itemTimer.getAccumlateTime() - lastHitTime > HitProtectTime || lastHitTime == 0) {
		lastHitTime = itemTimer.getAccumlateTime();
		AudioHelper::playFromBuffer(playerHurtAudio.wavBuffer);

		ParticleHelper* particleGroup = new ParticleHelper;
		particleGroup->addNewParticle(150, 25.0f, 1.6f, 0.6f, glm::vec4(1.0f, 0.1f, 0.1f, 1.0f), glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]));
		RenderManager::getInstance()->AddRenderObject(ParticleGroupUuid, particleGroup);
		isHitTime = true;

	
		if (nowLife -1 >=0) {
			nowLife--;
		}else{
			nowLife = 8;
		}
		GameInfoInterface::setMaxLife(maxLife);
		GameInfoInterface::setNowLife(nowLife);
	}
		
}


void Player::grazePlayer()
{
	AudioHelper::playFromBuffer(playerGrazeAudio.wavBuffer);
	ParticleHelper* particleGroup = new ParticleHelper;
	particleGroup->addNewParticle(1, 12.0f, 0.6f, 0.6f, glm::vec4(1.0f), glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]));
	RenderManager::getInstance()->AddRenderObject(ParticleGroupUuid, particleGroup);

	playerScore += 50;
}

void Player::addPower()
{
	if (basePower < 4.0f) {
		basePower += 0.1f;
	}
	else {
		basePower = 4.0f;
	}
	
}

void Player::addPoint()
{
	playerScore += 200;
}

void Player::addLife()
{
	if (nowLife < maxLife) {
		nowLife++;
		AudioHelper::playFromBuffer(playerExtentAudio.wavBuffer);	
	}
	else {
		if (nowBomb < maxBomb) {
			nowBomb++;
		}
	}
	GameInfoInterface::setNowLife(nowLife);
	GameInfoInterface::setNowBomb(nowBomb);
}

void Player::addBomb()
{
	if (nowBomb < maxBomb) {
		nowBomb++;
	}
	GameInfoInterface::setNowBomb(nowBomb);
}

void Player::addMoonPoint()
{
	if (moonLevel < maxMoonLevel) {
		if (moonPoint < maxMoonPoint) {
			moonPoint += 1;
		}
		else {
			moonPoint = 0;
			moonLevel++;
		}
	}
	else {
		moonLevel = maxMoonLevel;
	}
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
	if (glfwGetKey(screen, XCFrameInfo::keySlow) == GLFW_PRESS) {
		moveSpeed = moveSpeed / 1.5f * 0.40f;
		renderDecisionPoint = true;
	}
	if (glfwGetKey(screen, XCFrameInfo::keyUp) == GLFW_PRESS) {
		if ((NowPosition[1] + moveSpeed)*XCFrameInfo::FrameTop < XCFrameInfo::FrameTop)//
			NowPosition[1] += moveSpeed;
		setPlayerDirection(PLAYER_STANDBY);
		have_player_change_state = true;
	}

	if (glfwGetKey(screen, XCFrameInfo::keyDown) == GLFW_PRESS) {
		if ((NowPosition[1] - moveSpeed)*XCFrameInfo::FrameTop > XCFrameInfo::FrameBottom)
			NowPosition[1] -= moveSpeed;
		setPlayerDirection(PLAYER_STANDBY);
		have_player_change_state = true;
	}
	if (glfwGetKey(screen, XCFrameInfo::keyRight) == GLFW_PRESS) {
		if ((NowPosition[0] + moveSpeed)*XCFrameInfo::FrameRight < XCFrameInfo::FrameRight)
			NowPosition[0] += moveSpeed;
		setPlayerDirection(PLAYER_TURNRIGHT);
		have_player_change_state = true;
	}

	if (glfwGetKey(screen, XCFrameInfo::keyLeft) == GLFW_PRESS) {
		if ((NowPosition[0] - moveSpeed)*XCFrameInfo::FrameRight > XCFrameInfo::FrameLeft)
			NowPosition[0] -= moveSpeed;
		setPlayerDirection(PLAYER_TURNLEFT);
		have_player_change_state = true;
	}

	if (glfwGetKey(screen, XCFrameInfo::keyShoot) == GLFW_PRESS) {
		if (itemTimer.getAccumlateTime() - lastShootTime > 0.1) {
			NormalStrike *strikeRight = new NormalStrike(NowPosition[0] + 0.04f, NowPosition[1] + 0.07f, NowPosition[2]);
			NormalStrike *strikeLeft = new NormalStrike(NowPosition[0] - 0.04f, NowPosition[1] + 0.07f, NowPosition[2]);
			RenderManager::getInstance()->AddRenderObject(StrikeRenderGroupUuid, strikeRight, true);
			RenderManager::getInstance()->AddRenderObject(StrikeRenderGroupUuid, strikeLeft, true);

			lastShootTime = itemTimer.getAccumlateTime();
		}
	
	}

	if (glfwGetKey(screen, XCFrameInfo::keyItem) == GLFW_PRESS ) {
		if (nowBomb-1>=0) {
			GameInfoInterface::setMaxBomb(maxBomb);
			GameInfoInterface::setNowBomb(--nowBomb);
		}
	}
	if (glfwGetKey(screen, XCFrameInfo::keyItem2) == GLFW_PRESS && itemTimer.getAccumlateTime() > lastStartMoonTime + 0.22f) {
		if (!isMoonState) {
			if (moonLevel > 0) {
				isMoonState = true;
			}
		}
		else {
			isMoonState = false;
		}
		lastStartMoonTime = itemTimer.getAccumlateTime();
	}
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
		float interval = divideInfo[0] - imageSwapTime;
		if (playerSameStateTime < interval) {
			playerSameStateTime += imageSwapTime;
		}
		else {
			playerSameStateTime = 0;
		}
	}
}

