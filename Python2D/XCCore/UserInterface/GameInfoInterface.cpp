#include "GameInfoInterface.h"
#include "../../XCFrameInfo.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../XCRender/BlendHelper.h"
#include <string>
#include <iomanip>
#include <sstream>
GameInfoInterface* GameInfoInterface::pInterface = nullptr;
GameInfoInterface::GameInfoInterface()
{
}
GameInfoInterface * GameInfoInterface::getInstance()
{
	if (pInterface == nullptr)
		pInterface = new GameInfoInterface;
	return pInterface;
}
void GameInfoInterface::UserInterfaceInit()
{
	if (!isInit) {
		rankImage = new XCAdvImageHelper("assets/UI/rank.png");
		playerInfoImage1 = new XCAdvImageHelper("assets/UI/playerInfo.png");
		playerInfoImage2 = new XCAdvImageHelper("assets/UI/playerInfo2.png");

		fontHelper.FontASCIIInit();
		isInit = true;
	}
}

void GameInfoInterface::UserInterfaceRender()
{
	infoTimer.Tick();
	if (isInit) {
		if( (float)XCFrameInfo::ScreenWidth / (float)XCFrameInfo::ScreenHeight >= 1.6667f){//>scrren(16:10)
			BlendOneMinusAlphaStart
			//rank render start
			float rankWidth = (1.0f - XCFrameInfo::FrameRight) / 2.5f;
			float rankHeight = rankWidth / 4.5f;
			float rankX = XCFrameInfo::FrameRight + (1.0f - XCFrameInfo::FrameRight) / 2.0f;
			float rankY = 1.0f - rankHeight * 3;
			glm::mat4 rankMat;
			rankMat = glm::translate(rankMat, glm::vec3(rankX, rankY, 0.0f));
			rankMat = glm::scale(rankMat, glm::vec3(rankWidth, rankHeight, 1.0f));

			
			rankImage->setMvpMatrix(rankMat);
			rankImage->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
				IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 5, 1, 6 - gameRank));

			//hightscore render start
			float highScoreWidth = (1.0f - XCFrameInfo::FrameRight) / 4.0f;
			float highScoreHeight = highScoreWidth / 3.0f;
			float highScoreX = XCFrameInfo::FrameRight + highScoreWidth / 1.4f;
			float highScoreY = rankY - rankHeight - highScoreHeight * 2.0f;
			glm::mat4 highScoreMat;
			highScoreMat = glm::translate(highScoreMat, glm::vec3(highScoreX, highScoreY, 0.0f));
			highScoreMat = glm::scale(highScoreMat, glm::vec3(highScoreWidth, highScoreHeight, 1.0f));

			playerInfoImage2->setMvpMatrix(highScoreMat);
			playerInfoImage2->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
				IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 2, 3, 2, 3));

			//nowscore render start
			float nowScoreWidth = (1.0f - XCFrameInfo::FrameRight) / 4.0f;
			float nowScoreHeight = nowScoreWidth / 3.0f;
			float nowScoreX = highScoreX;
			float nowScoreY = highScoreY  - nowScoreWidth ;
			glm::mat4 nowScoreMat;
			nowScoreMat = glm::translate(nowScoreMat, glm::vec3(nowScoreX, nowScoreY, 0.0f));
			nowScoreMat = glm::scale(nowScoreMat, glm::vec3(nowScoreWidth, nowScoreHeight, 1.0f));

			playerInfoImage2->setMvpMatrix(nowScoreMat);
			playerInfoImage2->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
				IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 2, 3, 2, 2));

			//font start render
			float hsFontX = XCFrameInfo::FrameRight + (1.0f - XCFrameInfo::FrameRight) / 2 + highScoreWidth / 1.4f;
			float hsFontY = rankY - nowScoreHeight/2.6f;
			fontHelper.FontSetWidthAndHeight(XCFrameInfo::ScreenHeight, XCFrameInfo::ScreenWidth);
			static std::stringstream ss; ss.str(""); 
			ss << std::setfill('0') << std::setw(10) << highScore << std::endl;
			std::string highscoreStr;  ss >> highscoreStr;
			fontHelper.FontASCIIRender(highscoreStr, hsFontX, hsFontY, 0.5f, glm::vec4(0.8f,0.8f,0.8f, 0.6f));

			float nsFontX = hsFontX;
			float nsFontY = hsFontY - highScoreHeight * 1.3f;
			ss.str("");
			ss << std::setfill('0') << std::setw(10) << nowScore++ << std::endl;//////////test
			std::string nowscoreStr; ss >> nowscoreStr;
			fontHelper.FontASCIIRender(nowscoreStr, nsFontX, nsFontY, 0.5f, glm::vec4(0.8f, 0.8f, 0.8f, 0.6f));

			fontHelper.FontASCIIRender(std::to_string((int)infoTimer.getFramePerSecond()), 0.0f, 0.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.8f, 1.0f));//fps render

			float nowLifeWidth = (1.0f - XCFrameInfo::FrameRight) / 4.0f;
			float nowLifeHeight = nowLifeWidth / 3.0f;
			float nowLifeX = nowScoreX + nowLifeWidth /2.2f;
			float nowLifeY = nowScoreY - nowLifeWidth;
			glm::mat4 nowLifeMat;
			nowLifeMat = glm::translate(nowLifeMat, glm::vec3(nowLifeX, nowLifeY, 0.0f));
			nowLifeMat = glm::scale(nowLifeMat, glm::vec3(nowLifeWidth, nowLifeHeight, 1.0f));

			playerInfoImage2->setMvpMatrix(nowLifeMat);
			playerInfoImage2->Render(glm::vec3(), glm::vec4(1.0f,1.0f,1.0f,1.0f), 0.0f, glm::vec3(), glm::vec3(),
				IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 2, 3, 1, 3));
			
			BlendEnd
		}
	}
}

void GameInfoInterface::UserInterfaceRelease()
{
	if (isInit) {
		rankImage->Release();
		playerInfoImage1->Release();
		playerInfoImage2->Release();

		delete rankImage, playerInfoImage1, playerInfoImage2, pInterface;
		pInterface = nullptr;
		isInit = false;
	}
}

void GameInfoInterface::setRank(int rank)
{
	gameRank = rank;
}

void GameInfoInterface::setNowScore(long score)
{
	nowScore = score;
}

void GameInfoInterface::setHightScore(long score)
{
	highScore = score;
}

void GameInfoInterface::setNowBomb(int count)
{
	nowBomb = count;
}

void GameInfoInterface::setNowLife(int life)
{
	nowLife = life;
}
