#include "River.h"
#include "../../XCFrameInfo.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../XCRender/BlendHelper.h"
void River::bankRender()
{
	static glm::vec3 reshape = glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f);
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		river_bank->setMvpMatrix(model);
		river_bank->Render(glm::vec3(0.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
}
void River::bedRender()
{
	static glm::vec3 reshape = glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f);
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		river_bed->setMvpMatrix(model);
		river_bed->Render(glm::vec3(0.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
}
void River::treeRender()
{
	static glm::vec3 reshape = glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f);
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-0.5f, 0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		river_tree->setMvpMatrix(model);
		river_tree->Render(glm::vec3(0.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(0.5f));
		river_tree->setMvpMatrix(model);
		river_tree->Render(glm::vec3(0.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f)*reshape);
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0,1,0));
		model = glm::scale(model, glm::vec3(0.5f));
		river_tree->setMvpMatrix(model);
		river_tree->Render(glm::vec3(0.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.5f, -0.5f, 0.0f)*reshape);
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
		model = glm::scale(model, glm::vec3(0.5f));
		river_tree->setMvpMatrix(model);
		river_tree->Render(glm::vec3(0.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY+0.2f));
	}
}
void River::waterRender()
{
	static glm::vec3 reshape = glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f);
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)*reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		river_water->setMvpMatrix(model);
		river_water->Render(glm::vec3(0.0f), glm::vec4(1.0f), 0.0f, glm::vec3(0), glm::vec3(0.0f),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, renderX, renderY+0.2f));
	}
}
void River::BackgroundInit()
{
	if (!isInit) {
		river_bank = new XCAdvImageHelper("assets/Background/river/river_bank.png");
		river_bed = new XCAdvImageHelper("assets/Background/river/river_bed.png");
		river_tree = new XCAdvImageHelper("assets/Background/river/river_tree.png");
		river_water = new XCAdvImageHelper("assets/Background/river/river_water.png");
		isInit = true;
	}
}

void River::BackgroundRender()
{
	if (isInit) {
		BlendNormalStart
		{
			bedRender();
			waterRender();
			bankRender();
			treeRender();
		}
		BlendEnd
		if (renderX < 1.0f && renderY < 1.0f) {
			renderY += 0.0006f;
		}
		else {
			renderX = 0.0f;
			renderY = 0.0f;
		}
	}
}

void River::BackgroundRelease()
{
	if (isInit) {
		river_bank->Release();
		river_bed->Release();
		river_tree->Release();
		river_water->Release();
		isInit = false;
	}
}
