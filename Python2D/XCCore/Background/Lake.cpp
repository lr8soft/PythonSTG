#include "Lake.h"
#include "../XCRender/IRenderHelper.h"
#include "../../XCFrameInfo.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL3/gl3w.h>

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
		timer.Tick();

		glEnable(GL_BLEND);
		renderLakeImage();
		renderWaterImage();
		renderLeafImage();
		glDisable(GL_BLEND);
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
	glm::vec3 reshape = glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop,1.0f);
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		lake->setMvpMatrix(model);
		lake->Render(glm::vec3(0.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop,1, 1, renderX, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.5f, -0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		lake->setMvpMatrix(model);
		lake->Render(glm::vec3(0.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		lake->setMvpMatrix(model);
		lake->Render(glm::vec3(0.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-0.5f, 0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		lake->setMvpMatrix(model);
		lake->Render(glm::vec3(0.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
}

void LakeBackground::renderWaterImage()
{
	glm::vec3 reshape = glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		water->setMvpMatrix(model);
		water->Render(glm::vec3(0.0f), waterColor, 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 2, 2, waterX, waterY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.5f, -0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		water->setMvpMatrix(model);
		water->Render(glm::vec3(0.0f), waterColor, 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 2, 2, waterX, waterY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		water->setMvpMatrix(model);
		water->Render(glm::vec3(0.0f), waterColor, 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 2, 2, waterX, waterY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-0.5f, 0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		water->setMvpMatrix(model);
		water->Render(glm::vec3(0.0f), waterColor, 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 2, 2, waterX, waterY));
	}
}

void LakeBackground::renderLeafImage()
{
	glm::vec3 reshape = glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
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
