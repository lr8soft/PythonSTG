#include "DecisionPointSE.h"
#include "XCImageHelper.h"
#include "../../XCFrameInfo.h"
#include <GL3/gl3w.h>
void DecisionPointSpecialEffect::SpecialEffectInit()
{
	if (!isInit) {
		image = new XCImageHelper("assets/Item/decision.png", true);
		isInit = true;
	}
	
}

void DecisionPointSpecialEffect::SpecialEffectRender(float x, float y, float z)
{
	if (getIsInit()) {
		timer.Tick();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		image->Render(glm::vec3(x, y, z), glm::vec4(1.0f), glm::radians((float)timer.getAccumlateTime()*180.0f), glm::vec3(0, 0, 1), 
			glm::vec3(0.12f * XCFrameInfo::FrameRight,0.12f * XCFrameInfo::FrameTop,1.0f), IRenderHelper::GetSpecificTexture( 1, 1, 1, 1));

		image->Render(glm::vec3(x, y, z), glm::vec4(1.0f), glm::radians(-(float)timer.getAccumlateTime()*180.0f), glm::vec3(0, 0, 1),
			glm::vec3(0.12f * XCFrameInfo::FrameRight, 0.12f * XCFrameInfo::FrameTop, 1.0f), IRenderHelper::GetSpecificTexture( 1, 1, 1, 1));
		glDisable(GL_BLEND);
	}
}

void DecisionPointSpecialEffect::SpecialEffectRelease()
{
	image->Release();
	delete image;
}
