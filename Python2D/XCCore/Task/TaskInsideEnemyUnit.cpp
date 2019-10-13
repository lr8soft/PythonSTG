#include "TaskInsideEnemyUnit.h"
#include <GL3/gl3w.h>
#include "../XCRender/RenderManager.h"
#include "../XCRender/XCImageHelper.h"

TaskInsideEnemyUnit::TaskInsideEnemyUnit(std::string uuid, int waitFrame, int workInterval, int repeatTime,
	std::string enemyImage, glm::vec2 dInfo, glm::vec3 sInfo, glm::vec2 sbInfo, glm::vec2 wInfo,
	glm::vec3 iCoord, float v, float a, float agle, float agleA, int type):TaskInsideUnit(uuid, waitFrame, workInterval, repeatTime)
{
	imagePath = enemyImage;
	divideInfo = dInfo;
	scaleInfo = sInfo;
	standbyInfo = sbInfo;
	walkInfo = wInfo;
	initCoord = iCoord;

	velocity = v;
	acceleration = a;
	angle = agle;
	angleAcceleration = agleA;

	colorType = type;
}

void TaskInsideEnemyUnit::UnitInit()
{
	TaskInsideUnit::UnitInit();

	XCImageHelper *image = new XCImageHelper(imagePath, true);
	enemyImage = new EnemyRenderObject(image,divideInfo,scaleInfo,standbyInfo, walkInfo,
		initCoord,velocity, acceleration,  angle, angleAcceleration, colorType);
}

void TaskInsideEnemyUnit::UnitWork()
{
	if (waitFrame > 0) {
		waitFrame--;
	}
	else {
		if (!haveAddToQueue) {
			auto iterBegin = renderObjectGroup.begin();
			auto iterEnd = renderObjectGroup.end();
			for (auto object = iterBegin; object != iterEnd; object++) {
				RenderManager::getInstance()->AddRenderObject(parentUuid, *object);
			}
			RenderManager::getInstance()->AddRenderObject(parentUuid, enemyImage);
			haveAddToQueue = true;
		}
	}
}

void TaskInsideEnemyUnit::UnitRelease()
{
	TaskInsideUnit::UnitRelease();
}



////////////////////////////EnemyRenderObject Function/////////////////////////////////////////
EnemyRenderObject::EnemyRenderObject(IRenderHelper *ptr, glm::vec2 dInfo, glm::vec3 sInfo, glm::vec2 sbInfo, glm::vec2 wInfo,
	glm::vec3 iCoord, float v, float a, float agle, float agleA, int type)
{
	imageHelper = ptr;
	divideInfo = dInfo;
	scaleInfo = sInfo;
	standbyInfo = sbInfo;
	walkInfo = wInfo;
	initCoord = iCoord;

	velocity = v;
	acceleration = a;
	angle = agle;
	angleAcceleration = agleA;

	colorType = type;
}

void EnemyRenderObject::Init()
{
}

void EnemyRenderObject::Render()
{
	timer.Tick();
	float deltaTime = timer.getDeltaFrame();
	float pi = 3.1415926535f;
	initCoord[0] += velocity * cos(angle / 180.0f * pi) * deltaTime;
	initCoord[1] += velocity * sin(angle / 180.0f * pi) * deltaTime;
	angle += angleAcceleration * deltaTime;
	velocity += acceleration * deltaTime;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	int nowDivideX = 0;
	bool isAnti = false;
	if (angle == 0) {
		if (nowTexIndex < standbyInfo[1])
			nowTexIndex+=0.1f*deltaTime;
		else
			nowTexIndex = standbyInfo[0];
	}
	else {
		if (nowTexIndex < walkInfo[1])
			nowTexIndex += 0.1f*deltaTime;
		else
			nowTexIndex = walkInfo[0];

		if (angle>=90.0f && angle <=270.0f) {
			isAnti = true;
		}
	}

	imageHelper->Render(initCoord, glm::vec4(1.0f), glm::radians(isAnti ? 180.0f :0.0f), glm::vec3(0, 1, 0), scaleInfo,
		IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, divideInfo[0], divideInfo[1], (int)nowDivideX, colorType));

	glDisable(GL_BLEND);
}

void EnemyRenderObject::Release()
{
	imageHelper->Release();
	delete imageHelper;
}
