#include "TaskInsideEnemyUnit.h"
#include "../XCRender/RenderManager.h"
TaskInsideEnemyUnit::TaskInsideEnemyUnit(std::string uuid, int waitFrame, int workInterval, int repeatTime,
	std::string enemyImage, glm::vec2 divideInfo, glm::vec3 scaleInfo, glm::vec2 standbyInfo, glm::vec2 walkInfo,
	glm::vec3 initCoord, float velocity, float acceleration, float angle, float angleAcceleration):TaskInsideUnit(uuid, waitFrame, workInterval, repeatTime)
{

}

void TaskInsideEnemyUnit::UnitInit()
{
	TaskInsideUnit::UnitInit();
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
			haveAddToQueue = true;
		}
	}
}

void TaskInsideEnemyUnit::UnitRelease()
{
	TaskInsideUnit::UnitRelease();
}

void EnemyRenderObject::Init()
{
}

void EnemyRenderObject::Render()
{
}

void EnemyRenderObject::Release()
{
}
