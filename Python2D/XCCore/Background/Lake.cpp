#include "Lake.h"
#include "../XCRender/IRenderHelper.h"
#include "../../XCFrameInfo.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../XCRender/BlendHelper.h"

void LakeBackground::BackgroundInit()
{
	if (!isInit) {
		lake = new XCAdvImageHelper("assets/Background/lake/lake.png");
		leef = new XCAdvImageHelper("assets/Background/lake/leef.png");
		water = new XCAdvImageHelper("assets/Background/lake/water.png");

		isInit = true;
	}
}

void LakeBackground::BackgroundRender()
{
	if (isInit) {
		BlendNormalStart
		renderLakeImage();
		renderWaterImage();
		renderLeafImage();
		BlendEnd
		if (renderX < 1.0f && renderY < 1.0f) {
			renderX += 0.0006f;
			renderY += 0.0006f;
		}
		else {
			renderX = 0.0f;
			renderY = 0.0f;
		}
		if (waterX > 0.0f) {
			waterX -= 0.0002f;
		}
		else {
			waterX = 1.0f;
		}
			
	}
}

void LakeBackground::renderLakeImage()
{
	static glm::vec3 reshape = glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop,1.0f);
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		lake->setMvpMatrix(model);
		lake->Render(glm::vec3(0.0f), lakeColor, 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop,1, 1, renderX, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.5f, -0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		lake->setMvpMatrix(model);
		lake->Render(glm::vec3(0.0f), lakeColor, 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		lake->setMvpMatrix(model);
		lake->Render(glm::vec3(0.0f), lakeColor, 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-0.5f, 0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		lake->setMvpMatrix(model);
		lake->Render(glm::vec3(0.0f), lakeColor, 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
}

void LakeBackground::renderWaterImage()
{
	static glm::vec3 reshape = glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f);
	BlendAlphaOneStart
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.5f,1.0f));
		water->setMvpMatrix(model);
		water->Render(glm::vec3(0.0f), waterColor, 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 2, 2, waterX, waterY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.0f));
		water->setMvpMatrix(model);
		water->Render(glm::vec3(0.0f), waterColor, 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 2, 2, waterX, waterY));
	}
	
}

void LakeBackground::renderLeafImage()
{
	static glm::vec3 reshape = glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f);
	BlendOneMinusAlphaColorStart
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		leef->setMvpMatrix(model);
		leef->Render(glm::vec3(0.0f), glm::vec4(0.37f, 1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.5f, -0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		leef->setMvpMatrix(model);
		leef->Render(glm::vec3(0.0f), glm::vec4(0.37f, 1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		leef->setMvpMatrix(model);
		leef->Render(glm::vec3(0.0f), glm::vec4(0.37f, 1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-0.5f, 0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		leef->setMvpMatrix(model);
		leef->Render(glm::vec3(0.0f), glm::vec4(0.37f, 1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
}

void LakeBackground::BackgroundRelease()
{
	if (isInit) {
		lake->Release();
		leef->Release();
		water->Release();

		delete lake, leef, water;
		isInit = false;
	}
}
