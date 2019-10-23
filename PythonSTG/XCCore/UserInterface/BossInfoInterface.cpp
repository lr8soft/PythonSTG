#include "BossInfoInterface.h"
#include "../../XCFrameInfo.h"
#include <GL3/gl3w.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
BossInfoInterface* BossInfoInterface::pInstance = nullptr;
BossInfoInterface::BossInfoInterface()
{
}

BossInfoInterface * BossInfoInterface::getInstance()
{
	if (pInstance == nullptr) {
		pInstance = new BossInfoInterface;
	}
	return pInstance;
}

void BossInfoInterface::UserInterfaceInit()
{
	if (!isInit) {
		spellCardStar = new XCAdvImageHelper("assets/UI/spellcardStar.png");
		spellcardBackground = new XCAdvImageHelper("assets/UI/spellcardbackground.png");

		fontHelper.FontUnicodeInit(bossName);
		fontHelper.FontUnicodeInit(spellCardName);
		isInit = true;
	}
}

void BossInfoInterface::UserInterfaceRender()
{
	if (isInit) {
		fontHelper.SetHeightAndWidth(XCFrameInfo::ScreenHeight, XCFrameInfo::ScreenWidth);
		float starWidth = 0.03f;
		float starHeight = 0.03f;
		float startX = - (1.0f-XCFrameInfo::FrameRight) - starWidth * 3.0f;
		float startY = 1.0f - starHeight * 3;

		fontHelper.FontUnicodeRender(bossName, (1.0f - XCFrameInfo::FrameRight)/2.0f + starWidth/2.3f, startY + starHeight * 2, 0.3f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		for (int i = 0; i < spellCardCount;i++) {
			glm::mat4 starMat;
			starMat = glm::translate(starMat, glm::vec3(startX + starWidth * i, startY, 0.0f));
			starMat = glm::scale(starMat, glm::vec3(starWidth, starHeight, 1.0f));
			spellCardStar->setMvpMatrix(starMat);
			spellCardStar->Render(glm::vec3(), glm::vec4(0.0f,1.0f, 0.0f, 1.0f), 0.0f, glm::vec3(), glm::vec3(),
				IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1, 1));
		}
		glDisable(GL_BLEND);

		float spellCardBackgroundWidth = spellcardBackground->getWidth() * 0.002f;
		float spellCardBackgroundHeight = spellcardBackground->getHeight() * 0.002f;
		float backgroundX = (1.0f - XCFrameInfo::FrameRight) / 2.0f + spellCardBackgroundHeight;
		float backgroundY = 1.0f - spellCardBackgroundHeight * 1.2f;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glm::mat4 backgroundMat;
		backgroundMat = glm::translate(backgroundMat, glm::vec3(backgroundX, backgroundY, 0.0f));
		backgroundMat = glm::scale(backgroundMat, glm::vec3(spellCardBackgroundWidth, spellCardBackgroundHeight, 1.0f));
		spellcardBackground->setMvpMatrix(backgroundMat);
		spellcardBackground->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1, 1));
		glDisable(GL_BLEND);
		fontHelper.FontUnicodeRender(spellCardName,
			(1.0f - XCFrameInfo::FrameRight) / 2.0f + XCFrameInfo::FrameRight /(1.1f + spellCardName.length() * 0.02f), 1.0f - spellCardBackgroundHeight * 0.8f, 0.5f, glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	}
}

void BossInfoInterface::UserInterfaceRelease()
{
	if (isInit) {
		spellCardStar->Release();
		spellcardBackground->Release();
		delete spellCardStar, spellcardBackground;
		spellCardStar = nullptr;
		spellcardBackground = nullptr;

		delete pInstance;
		pInstance = nullptr;
		isInit = false;
	}
}

void BossInfoInterface::setSpellCardCount(int count)
{
	spellCardCount = count;
}

void BossInfoInterface::setSpellCardName(std::string name)
{
	spellCardName = name;
	fontHelper.FontUnicodeInit(name);
}

void BossInfoInterface::setBossName(std::string name)
{
	bossName = name;
	fontHelper.FontUnicodeInit(name);
}
