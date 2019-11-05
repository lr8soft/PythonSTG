#include "GameInfoInterface.h"
#include "../../XCFrameInfo.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../XCRender/BlendHelper.h"
#include <string>
#include <iomanip>
#include <sstream>
GameInfoInterface* GameInfoInterface::pInterface = nullptr;
int GameInfoInterface::nowLife = 2, GameInfoInterface::maxLife = 8;
int GameInfoInterface::nowBomb = 2, GameInfoInterface::maxBomb = 8;
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
		lifeBombImage = new XCAdvImageHelper("assets/UI/lifebomb.png");

		moonUIImage = new XCAdvImageHelper("assets/UI/pointslot.png");
		moonUIContext = new XCAdvImageHelper("assets/UI/uistick.png");

		fontHelper.FontASCIIInit();
		isInit = true;
	}
}

void GameInfoInterface::UserInterfaceRender()
{
	if (isInit) {
		timer.Tick();
		//if( (float)XCFrameInfo::ScreenWidth / (float)XCFrameInfo::ScreenHeight >= 1.6667f){//>scrren(16:10)
			float ScaleRate = (float)XCFrameInfo::ScreenHeight / 720.0f;

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
			BlendEnd

			//font start render
			float hsFontX = XCFrameInfo::FrameRight + (1.0f - XCFrameInfo::FrameRight) / 2 + highScoreWidth / 1.4f;
			float hsFontY = rankY - nowScoreHeight/2.6f;
			fontHelper.SetHeightAndWidth(XCFrameInfo::ScreenHeight, XCFrameInfo::ScreenWidth);
			static std::stringstream ss; ss.str(""); 
			ss << std::setfill('0') << std::setw(10) << highScore << std::endl;
			static std::string highscoreStr;  ss >> highscoreStr;
			fontHelper.FontASCIIRender(highscoreStr, hsFontX, hsFontY, 0.5f * ScaleRate, glm::vec4(0.8f,0.8f,0.8f, 0.6f));

			float nsFontX = hsFontX;
			float nsFontY = hsFontY - highScoreHeight * 1.3f;
			ss.str("");
			ss << std::setfill('0') << std::setw(10) << nowScore << std::endl;//////////test
			static std::string nowscoreStr; ss >> nowscoreStr;
			fontHelper.FontASCIIRender(nowscoreStr, nsFontX, nsFontY, 0.5f * ScaleRate, glm::vec4(0.8f, 0.8f, 0.8f, 0.6f));
			
			float nowLifeImageWidth = (1.0f - XCFrameInfo::FrameRight) / 4.0f;
			float nowLifeImageHeight = nowLifeImageWidth / 3.0f;
			float nowLifeImageX = nowScoreX;
			float nowLifeImageY = nowScoreY - nowLifeImageWidth * 1.2f;
			glm::mat4 nowLifeMat;
			nowLifeMat = glm::translate(nowLifeMat, glm::vec3(nowLifeImageX, nowLifeImageY, 0.0f));
			nowLifeMat = glm::scale(nowLifeMat, glm::vec3(nowLifeImageWidth, nowLifeImageHeight, 1.0f));

			BlendOneMinusAlphaStart
			playerInfoImage2->setMvpMatrix(nowLifeMat);
			playerInfoImage2->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
				IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 2, 3, 1, 3));
			BlendEnd

			float nowBombImageWidth = (1.0f - XCFrameInfo::FrameRight) / 4.5f;
			float nowBombImageHeight = nowBombImageWidth / 3.0f;
			float nowBombImageX = nowScoreX / 1.02f;
			float nowBombImageY = nowLifeImageY - nowBombImageWidth;
			glm::mat4 nowBombMat;
			nowBombMat = glm::translate(nowBombMat, glm::vec3(nowBombImageX, nowBombImageY, 0.0f));
			nowBombMat = glm::scale(nowBombMat, glm::vec3(nowBombImageWidth, nowBombImageHeight, 1.0f));
			BlendOneMinusAlphaStart
				playerInfoImage2->setMvpMatrix(nowBombMat);
			playerInfoImage2->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
				IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 2, 3, 1, 2));
			BlendEnd

			renderPlayerLife(nowLifeImageX + nowLifeImageWidth / 2.0f, nowLifeImageY );
			renderPlayerBomb(nowLifeImageX + nowLifeImageWidth / 2.0f, nowBombImageY);

			float moonWidth = (1.0f - XCFrameInfo::FrameRight) / 1.5f;
			float moonHeight = moonWidth / 2.3091f;//³ýÒÔ¿í³¤±È
			float moonX = -1.0f + (1.0f - XCFrameInfo::FrameRight) + moonWidth / 1.5f;
			float moonY = -1.0f + moonHeight * 1.5f;
			BlendOneMinusAlphaStart
			{

				glm::mat4 moonMatrix;
				moonMatrix = glm::translate(moonMatrix, glm::vec3(moonX, moonY, 0.0f));
				moonMatrix = glm::scale(moonMatrix, glm::vec3(moonWidth, moonHeight, 1.0f));
				moonUIImage->setMvpMatrix(moonMatrix);
				moonUIImage->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
					IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1, 1));

				float specialX = -1.0f + (1.0f - XCFrameInfo::FrameRight) + moonWidth / 1.6f;
				glm::mat4 contextMatrix;
				contextMatrix = glm::translate(contextMatrix, glm::vec3(specialX, moonY, 0.0f));
				contextMatrix = glm::scale(contextMatrix, glm::vec3(moonWidth * 0.5826f, moonWidth/ 30.8f  * 0.5f, 1.0f));
				moonUIContext->setMvpMatrix(contextMatrix);
				moonUIContext->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
					IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 2, 1, 2));

				float nowPointWidth = (moonWidth * 0.5826f) * (moonPoint * 1.0f/ maxMoonPoint * 1.0f);
				float nowPointX = specialX - (moonWidth * 0.5826f - nowPointWidth) / 2.0f;
				glm::mat4 contextMatrix2;
				contextMatrix2 = glm::translate(contextMatrix2, glm::vec3(nowPointX, -1.0f + moonHeight * 1.28f, 0.0f));
				contextMatrix2 = glm::scale(contextMatrix2, glm::vec3(nowPointWidth, moonWidth / 30.8f  * 0.8f, 1.0f));
				moonUIContext->setMvpMatrix(contextMatrix2);
				moonUIContext->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
					IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 2, moonIndex, 1));

				fontHelper.FontASCIIRender(std::to_string(moonLevel),
					(1.0f - XCFrameInfo::FrameRight) / 2.0f + moonWidth / 3.6f, moonHeight * 0.85f, 0.3f * ScaleRate, glm::vec4(0.8f, 0.8f, 0.8f, 0.6f));
				if (moonIndex < 1.0f) {
					moonIndex += timer.getDeltaFrame() / 10.0f;
				}
				else {
					moonIndex = 0.0f;
				}
			}
			BlendEnd
	}
}

GameInfoInterface::GameInfoInterface()
{
}

void GameInfoInterface::renderPlayerLife(float x, float y)
{
	BlendOneMinusAlphaStart

	float scaleSize = 0.002f;
	float lifeWidth = (1.0f - XCFrameInfo::FrameRight) / 13.0f;
	float lifeHeight = lifeWidth;

	for (int i = 0; i < nowLife;i++) {
		glm::mat4 lifeMat;
		lifeMat = glm::translate(lifeMat, glm::vec3(x + lifeWidth * i, y, 0.0f));
		lifeMat = glm::scale(lifeMat, glm::vec3(lifeWidth, lifeHeight, 1.0f));
		lifeBombImage->setMvpMatrix(lifeMat);
		lifeBombImage->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 4, 3, 2, 3));
	}
	for (int j = 0; j < maxLife - nowLife; j++) {
			glm::mat4 lifeMat;
		lifeMat = glm::translate(lifeMat, glm::vec3(x + lifeWidth *(nowLife+j), y, 0.0f));
		lifeMat = glm::scale(lifeMat, glm::vec3(lifeWidth, lifeHeight, 1.0f));
		lifeBombImage->setMvpMatrix(lifeMat);
		lifeBombImage->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 4, 3, 1, 3));
	}


	BlendEnd
}

void GameInfoInterface::renderPlayerBomb(float x, float y)
{
	BlendOneMinusAlphaStart

	float scaleSize = 0.002f;
	float lifeWidth = (1.0f - XCFrameInfo::FrameRight) / 13.0f;
	float lifeHeight = lifeWidth;

	for (int i = 0; i < nowBomb; i++) {
		glm::mat4 lifeMat;
		lifeMat = glm::translate(lifeMat, glm::vec3(x + lifeWidth * i, y, 0.0f));
		lifeMat = glm::scale(lifeMat, glm::vec3(lifeWidth, lifeHeight, 1.0f));
		lifeBombImage->setMvpMatrix(lifeMat);
		lifeBombImage->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 4, 3, 4, 3));
	}
	for (int j = 0; j < maxBomb - nowBomb; j++) {
		glm::mat4 lifeMat;
		lifeMat = glm::translate(lifeMat, glm::vec3(x + lifeWidth * (nowBomb + j), y, 0.0f));
		lifeMat = glm::scale(lifeMat, glm::vec3(lifeWidth, lifeHeight, 1.0f));
		lifeBombImage->setMvpMatrix(lifeMat);
		lifeBombImage->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 4, 3, 3, 3));
	}

	BlendEnd
}

void GameInfoInterface::UserInterfaceRelease()
{
	if (isInit) {
		rankImage->Release();
		playerInfoImage1->Release();
		playerInfoImage2->Release();
		lifeBombImage->Release();

		delete rankImage, playerInfoImage1, playerInfoImage2, pInterface, lifeBombImage;
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

void GameInfoInterface::setSpellCardRemainTime(float time)
{
	spellCardRemainTime = time;
}

void GameInfoInterface::setNowBomb(int count)
{
	nowBomb = count;
}

void GameInfoInterface::setNowLife(int life)
{
	nowLife = life;
}

void GameInfoInterface::setMaxBomb(int count)
{
	maxBomb = count;
}

void GameInfoInterface::setMaxLife(int count)
{
	maxLife = count;
}


void GameInfoInterface::setMoonPoint(long currentPoint, long max)
{
	moonPoint = currentPoint;
	maxMoonPoint = max;
}

void GameInfoInterface::setMoonLevel(int level, int max)
{
	moonLevel = level;
	maxLevel = max;
}
