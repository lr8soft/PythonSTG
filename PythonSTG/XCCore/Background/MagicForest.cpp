#include "MagicForest.h"
#include "../XCRender/IRenderHelper.h"
#include "../../XCFrameInfo.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../XCRender/BlendHelper.h"


void MagicForest::BackgroundInit()
{
	if (!isInit) {
		mask = new XCAdvImageHelper("assets/Background/magicforest/mask.png");
		ground = new XCAdvImageHelper("assets/Background/magicforest/ground.png");

		float offset = 2.0f;
		camera.setPosition(glm::vec3(0.0f, 0.0f - offset, 2.0f));
		camera.setTarget(glm::vec3(0.0f, 1.155f - offset,0.0f));
		camera.setUp(glm::vec3(0.0f,2.0f - offset, 3.155f));
		isInit = true;
	}
}

void MagicForest::BackgroundRender()
{
	if (isInit) {
		BlendOneMinusAlphaStart
		renderGroundImage();
		renderMaskImage();
		BlendEnd

		if (renderY < 1.0f) {
			renderY += 0.0006f;
		}
		else {
			renderY = 0.0f;
		}

		if (maskY < 1.0f) {
			maskY += 0.0012f;
		}
		else {
			maskY = 0.0f;
		}
	}
}

void MagicForest::renderGroundImage()
{
	glm::vec3 reshape = glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f);

	glm::mat4 projecetion = camera.getProjectionMatrix();
	glm::mat4 view = camera.getViewMatrix();

	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(3.0f, 1.0f, 0.0f) * reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		ground->setMvpMatrix(projecetion* view * model);
		ground->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1.0f, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-3.0f, 1.0f, 0.0f) * reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		ground->setMvpMatrix(projecetion* view * model);
		ground->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1.0f, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(1.0f, 1.0f, 0.0f) * reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		ground->setMvpMatrix(projecetion* view * model);
		ground->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1.0f, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-1.0f, 1.0f, 0.0f) * reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		ground->setMvpMatrix(projecetion* view * model);
		ground->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1.0f, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 0.0f) * reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		ground->setMvpMatrix(projecetion* view * model);
		ground->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1.0f, renderY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(1.0f, -1.0f, 0.0f) * reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		ground->setMvpMatrix(projecetion* view * model);
		ground->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1.0f, renderY));
	}
}

void MagicForest::renderMaskImage()
{
	glm::vec3 reshape = glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f);

	glm::mat4 projecetion = camera.getProjectionMatrix();
	glm::mat4 view = camera.getViewMatrix();
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(3.0f, 1.0f, 0.0f) * reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		mask->setMvpMatrix(projecetion* view * model);
		mask->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1.0f, maskY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-3.0f, 1.0f, 0.0f) * reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		mask->setMvpMatrix(projecetion* view * model);
		mask->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1.0f, maskY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(1.0f, 1.0f, 0.0f) * reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		mask->setMvpMatrix(projecetion* view * model);
		mask->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1.0f, maskY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-1.0f, 1.0f, 0.0f) * reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		mask->setMvpMatrix(projecetion* view * model);
		mask->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1.0f, maskY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 0.0f) * reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		mask->setMvpMatrix(projecetion* view * model);
		mask->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1.0f, maskY));
	}
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(1.0f, -1.0f, 0.0f) * reshape);
		model = glm::scale(model, glm::vec3(1.0f));
		mask->setMvpMatrix(projecetion* view * model);
		mask->Render(glm::vec3(), glm::vec4(1.0f), 0.0f, glm::vec3(), glm::vec3(),
			IRenderHelper::GetSpecificTexWithRatef(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1, 1, 1.0f, maskY));
	}
}

void MagicForest::BackgroundRelease()
{
	if (isInit) {
		mask->Release();
		ground->Release();

		delete mask, ground;
		isInit = false;
	}
}
