#include "RectangleTypeBullet.h"
#include "../../XCFrameInfo.h"
#include "../XCCollide/CollideInfo.h"
#include "../XCRender/ParticleHelper.h"
#include "../XCRender/RenderManager.h"
#include <GL3/gl3w.h>
#include <iostream>
RectangleTypeBullet::RectangleTypeBullet(std::string bulletImagePath, glm::vec4 dInfo, glm::vec3 sInfo,glm::vec3 cSize ,glm::vec3 initCoord,
	float v, float a, float agl, float incA, int rbTime, bool ap,
	int pDensity, float pFinishTime, float pVelocity, float pSize, glm::vec4 pColor)
{
	imagePath = bulletImagePath;

	divideInfo = dInfo;
	scaleInfo = sInfo;
	collideSize = cSize;
	NowPosition[0] = initCoord[0];
	NowPosition[1] = initCoord[1];
	NowPosition[2] = initCoord[2];

	velocity = v;
	acceleration = a;
	angle = agl;
	increaseAngle = incA;
	reBoundTime = rbTime;
	aimToPlayer = ap;
	//release part
	particleDensity = pDensity;
	particleFinishTime = pFinishTime;
	particleVelocity = pVelocity;
	particleSize = pSize;
	particleColor = pColor;

	//define current type
	setCurrentType(BulletType);
}

void RectangleTypeBullet::Init()
{
	if (!isInit) {
		image = new XCImageHelper(imagePath, true);
		isInit = true;
	}
}

void RectangleTypeBullet::Render()
{
	if (isInit) {
		timer.Tick();
		auto pPlayerHelper1 = CollideInfo::getCollideHelper();
		float* playerPos = (pPlayerHelper1 == nullptr ? nullptr : pPlayerHelper1->getPlayerPosition());
		Bullet::solveBulletMovement(aimToPlayer, playerPos, velocity, angle, acceleration, increaseAngle, timer.getDeltaFrame());

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		image->Render(glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]), glm::vec4(1.0f), glm::radians(angle), glm::vec3(0, 0, 1),
			scaleInfo * glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f),
			IRenderHelper::GetSpecificTexture(divideInfo[0], divideInfo[1], divideInfo[2], divideInfo[3]));
		glDisable(GL_BLEND);
		if (Bullet::checkReboundOrOverflow(&reBoundTime, &angle, collideSize[0], collideSize[1])) {//超出边界不渲染结束特效
			isWorkFinish = true;
		}
	}
}
void RectangleTypeBullet::Release()
{
	if (isInit) {
		image->Release();
		delete image;

		isInit = false;
	}
}

bool RectangleTypeBullet::BulletCollideWithPoint(float x, float y, bool &haveGraze)
{
	bool value = false;
	if (isInit && timer.getAccumlateTime() >= 0.2f) {
		x -= NowPosition[0];
		y -= NowPosition[1];

		float theta = glm::radians(angle);
		float NewX = x * cos(theta) + y * sin(theta);
		float NewY = -x * sin(theta) + y * cos(theta);

		float distance = pow(NewX, 2) + pow(NewY, 2);

		if (!haveCheckGraze && distance <= CollideInfo::getGrazeDistance()) {
			haveGraze = true;
			haveCheckGraze = true;
		}
		float parameterX = collideSize.x;
		float parameterY =  collideSize.y;
		if (NewX >=  -parameterX && NewX <=  parameterX) {
			if (NewY >= -parameterY && NewY <= parameterY) {
				value = true;
			}
		}
	
	}

	return value;
}

void RectangleTypeBullet::setBulletTerminate()
{
	ParticleHelper* particleGroup = new ParticleHelper;
	particleGroup->addNewParticle(particleDensity, particleSize, particleVelocity, particleFinishTime, particleColor,
		glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]));
	RenderManager::getInstance()->AddRenderObject(ParticleGroupUuid, particleGroup);
	isWorkFinish = true;
}
