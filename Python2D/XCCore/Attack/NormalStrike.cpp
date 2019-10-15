#include "NormalStrike.h"
#include "../../XCFrameInfo.h"

#include <GL3/gl3w.h>
XCWavFile NormalStrike::strikeEffect;
bool NormalStrike::isResInit = false;
NormalStrike::NormalStrike(float x, float y, float z)
{
	NowPosition[0] = x;
	NowPosition[1] = y;
	NowPosition[2] = z;

	setCurrentType(AttackType);
}

void NormalStrike::Init()
{
	if (!isInit) {
		if (!isResInit) {
			strikeEffect = AudioHelper::loadWavFromFile("assets/SE/se_plst00.wav");
			isResInit = true;
		}
		
		renderHelper = new XCImageHelper("assets/Item/attack.png", true);
		isInit = true;
	}
}

void NormalStrike::Render()
{
	if (isInit) {
		timer.Tick();

		AudioHelper::playFromBuffer(strikeEffect.wavBuffer);
		NowPosition[1] += velocity * timer.getDeltaFrame();

		float height = 0.075f;
		float width = height /(1.0f * renderHelper->getImageWidth() / renderHelper->getImageHeight());
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		renderHelper->Render(glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]), 
			glm::vec4(1.0f), glm::radians(90.0f), glm::vec3(0, 0, 1), glm::vec3(width, height, 0.05f),
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 4, 1, 1, 1));
		glDisable(GL_BLEND);

		if (NowPosition[1]>1.0f + 0.025f) {
			isWorkFinish = true;
		}
	}
}

void NormalStrike::Release()
{
	if (isInit) {
		renderHelper->Release();
		delete renderHelper;

		isInit = false;
	}
}

void NormalStrike::checkCollisonWithEnemy(EnemyObject * pEnemy)
{
}
