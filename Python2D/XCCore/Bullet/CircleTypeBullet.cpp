#include "CircleTypeBullet.h"
#include "../../XCFrameInfo.h"
#include "../XCCollide/CollideInfo.h"
#include <GL3/gl3w.h>
#include <iostream>
CircleTypeBullet::CircleTypeBullet(std::string bulletImagePath, glm::vec4 dInfo, glm::vec3 sInfo, glm::vec3 cSize,glm::vec3 initCoord, 
	float v, float a, float agl, float incA, int rbTime,bool ap, 
	int pDensity, float pFinishTime, float pVelocity, float pSize, glm::vec4 pColor)
{
	//init part
	imagePath = bulletImagePath;
	divideInfo = dInfo;
	scaleInfo = sInfo;
	collideSize = cSize;
	NowPosition[0] = initCoord[0];
	NowPosition[1] = initCoord[1];
	NowPosition[2] = initCoord[2];
	//work part
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
}

void CircleTypeBullet::Init()
{
	if (!isInit) {
		image = new XCImageHelper(imagePath, true);
		explodeSpecialEffect = new ExplodeParticleSpecialEffect(particleDensity, particleSize, particleFinishTime, particleVelocity, particleColor);
		explodeSpecialEffect->SpecialEffectGLInit();
		isInit = true;
	}
}

void CircleTypeBullet::Render()
{
	if (isInit) {
		timer.Tick();
		if (!isFinishTime) {
			auto pPlayerHelper1 = CollideInfo::getCollideHelperP1();
			float* playerPos = (pPlayerHelper1 == nullptr ? nullptr : pPlayerHelper1->getPlayerPosition() );
			Bullet::solveBulletMovement(aimToPlayer, playerPos, velocity, angle, acceleration, increaseAngle, timer.getDeltaFrame());


			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			image->Render(glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]), glm::vec4(1.0f), glm::radians(angle), glm::vec3(0, 0, 1),
				scaleInfo * glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f),
				IRenderHelper::GetSpecificTexture(divideInfo[0], divideInfo[1], divideInfo[2], divideInfo[3]));
			glDisable(GL_BLEND);
			if (Bullet::checkReboundOrOverflow(&reBoundTime, &angle, scaleInfo[0], scaleInfo[1])) {//超出边界不渲染结束特效
				isWorkFinish = true;
			}
		}
		else {
			if (timer.getNowFrame() - nowFinishTime < particleFinishTime) {
				explodeSpecialEffect->SpecialEffectCoordInit(glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]));
				explodeSpecialEffect->SpecialEffectRender();
			}
			else {
				isWorkFinish = true;
			}
		}

	}
}

void CircleTypeBullet::startFinishEffect()
{
	isFinishTime = true;
	nowFinishTime = timer.getNowFrame();	
}
void CircleTypeBullet::Release()
{
	if (isInit) {
		image->Release();
		explodeSpecialEffect->SpecialEffectRelease();
		delete image, explodeSpecialEffect;

		image = nullptr;
		explodeSpecialEffect = nullptr;
		isInit = false;
	}
}

bool CircleTypeBullet::BulletCollideWithPoint(float x, float y,bool &haveGraze)
{
	bool value = false;
	if (isInit && !isFinishTime && timer.getAccumlateTime() >=0.4f) {
		float distance = (x - NowPosition[0])*(x - NowPosition[0]) + (y - NowPosition[1])*(y - NowPosition[1]);
		float parameter = collideSize[0] * collideSize[0];

		if (!haveCheckGraze && distance <= CollideInfo::getGrazeDistance()) {
			haveGraze = true;
			haveCheckGraze = true;
		}
		value = (distance < parameter);
	}

	return value;
}
