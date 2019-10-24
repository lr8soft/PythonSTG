#include "NormalStrike.h"
#include "../../XCFrameInfo.h"
#include "../XCRender/RenderManager.h"
#include "../XCRender/ParticleHelper.h"
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
		
		AudioHelper::playFromBuffer(strikeEffect.wavBuffer);

		renderHelper = new XCImageHelper("assets/Item/attack.png", true);	

		scaleSize[1] = 0.075f;
		scaleSize[0] = scaleSize[1] / (1.0f * renderHelper->getImageWidth() / renderHelper->getImageHeight());
		scaleSize[2] = 0.075f;
		
		isInit = true;
	}
}

void NormalStrike::Render()
{
	if (isInit) {
		timer.Tick();
		NowPosition[1] += velocity * timer.getDeltaFrame();
		if (isFinish && texIndex < 4) {
			texIndex += 1.0f;
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		renderHelper->Render(glm::vec3(NowPosition[0], NowPosition[1], NowPosition[2]), 
			glm::vec4(1.0f), glm::radians(90.0f), glm::vec3(0, 0, 1), glm::vec3(scaleSize[0], scaleSize[1], scaleSize[2]),
			IRenderHelper::GetSpecificTexWithRate(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 4, 1, (int)texIndex, 1));
		glDisable(GL_BLEND);

		if (!haveEffectPlay) {
			AudioHelper::playFromBuffer(strikeEffect.wavBuffer);
			haveEffectPlay = true;
		}

		if (NowPosition[1]>1.0f + 0.025f) {
			isWorkFinish = true;
		}
		
		if (isFinish && timer.getAccumlateTime() - finishTime > 0.06) {
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

void NormalStrike::checkCollisionWithBoss(BossObject * pBoss)
{
	if (!pBoss->getIsTerminate() && !isFinish) {
		glm::vec2 bossPosition = pBoss->getPosition();
		float collisionRadius = pBoss->getBossCollisionRadius();

		float halfWidth = scaleSize[1];
		float halfHeight = scaleSize[0];
		float width = halfWidth * 2;
		float height = halfHeight * 2;

		float distX = abs(bossPosition.x - NowPosition[0]);
		float distY = abs(bossPosition.y - NowPosition[1]);

		if (distX > (width / 2 + collisionRadius)) return; 
		if (distY > (height / 2 + collisionRadius)) return; 

		float cornerDistance_sq = pow((distX - width / 2), 2) + pow(distY - height / 2, 2);
		if (distX <= (width / 2) || distY <= (height / 2) || cornerDistance_sq <= pow(collisionRadius, 2)) {
			ParticleHelper* particleGroup = new ParticleHelper;
			particleGroup->addNewParticle(6, 15.0f, 0.6f, 0.4f, glm::vec4(1.0f), glm::vec3(NowPosition[0], NowPosition[1],0.0f));
			RenderManager::getInstance()->AddRenderObject(ParticleGroupUuid, particleGroup);

			pBoss->hurtBossObject(0.2f);
			velocity /= 3.0f;
			finishTime = timer.getAccumlateTime();
			isFinish = true;
		}
	}
}

void NormalStrike::checkCollisionWithEnemy(EnemyObject * pEnemy)
{
	if (!pEnemy->getIsTerminate() && !isFinish) {
		glm::vec3 enemyPosition = pEnemy->getNowPosition();
		float halfWidth = scaleSize[1];
		float halfHeight = scaleSize[0];
		float lastY = NowPosition[1] - velocity * timer.getDeltaFrame();
		if (enemyPosition[0] <= NowPosition[0] + halfWidth && enemyPosition[0] >= NowPosition[0] - halfWidth){
			if (enemyPosition[1] <= NowPosition[1] + halfHeight && enemyPosition[1] >= lastY - halfHeight) {
				ParticleHelper* particleGroup = new ParticleHelper;
				particleGroup->addNewParticle(6, 15.0f, 0.6f, 0.4f, glm::vec4(1.0f), enemyPosition);
				RenderManager::getInstance()->AddRenderObject(ParticleGroupUuid, particleGroup);

				pEnemy->hurtEnemy(0.2f);
				velocity /= 3.0f;
				finishTime = timer.getAccumlateTime();
				isFinish = true;
			}
		}
	}
}

void NormalStrike::threadStrikeHitWork()
{
	AudioHelper::playFromBuffer(strikeEffect.wavBuffer);
}