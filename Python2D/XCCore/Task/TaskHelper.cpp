#include "TaskHelper.h"
#include "../Bullet/BulletHelper.h"
#include "TaskEnemy.h"
TaskInsideUnit * TaskHelper::parseTaskUnitFromObject(std::string uuid, PyObject * unitObject)
{
	TaskInsideUnit* unit  = nullptr;
	if (unitObject != nullptr) {
		auto unitSizeInfo = PyObject_CallMethod(unitObject, "_cpp_getBulletSize", NULL);
		auto unitDetailInfo = PyObject_CallMethod(unitObject, "_cpp_getUnitInfo", NULL);

		int renderObjectSize;
		PyArg_Parse(unitSizeInfo, "i", &renderObjectSize);

		int waitFrame, workInterval, repeatTime;
		PyArg_ParseTuple(unitDetailInfo, "iii", &waitFrame, &workInterval, &repeatTime);

		unit = new TaskInsideUnit(uuid, waitFrame, workInterval, repeatTime);//R  E  L  E  A  S  E     P  L  E  A S  E
		
		std::list<std::list<RenderObject*>> renderGroupGroup;
		for (int i = 0; i < repeatTime - 1;i++) {
			std::list<RenderObject*> list;
			renderGroupGroup.push_back(list);
		}

		if (renderObjectSize>0) {
			for (int i = 0; i < renderObjectSize;i++) {
				PyObject* pBullet, *bulletObject = PyObject_CallMethod(unitObject, "_cpp_getBulletItem", NULL);
				PyArg_Parse(bulletObject, "O", &pBullet);

				Bullet* bulletItem = BulletHelper::parseBulletObject(pBullet);
				if (bulletItem !=nullptr) {
					unit->addRenderObject(bulletItem);
				}
				if (repeatTime > 1) {
					for (auto iter = renderGroupGroup.begin(); iter != renderGroupGroup.end(); iter++) {
						Bullet* newBullet = BulletHelper::parseBulletObject(pBullet);
						iter->push_back(newBullet);
					}
				}
			}
			for (auto iter = renderGroupGroup.begin(); iter != renderGroupGroup.end(); iter++) {
				unit->addRenderGroup(*iter);
			}
		}

	}
	return unit;
}

Task * TaskHelper::parseTaskFromObject(PyObject * taskObject)
{
	Task* task = nullptr;
	if (taskObject != nullptr) {
		auto taskInfo = PyObject_CallMethod(taskObject, "_cpp_getTaskInfo", NULL);
		auto sizeInfo = PyObject_CallMethod(taskObject, "_cpp_getUnitSize", NULL);

		const char *uuid, *targetUuid; int repeatTime, intervalFrame, isEnemyTask = 0;
		PyArg_ParseTuple(taskInfo, "ssii|p", &uuid, &targetUuid, &repeatTime, &intervalFrame, &isEnemyTask);
		if (!isEnemyTask) {
			task = new Task(uuid, targetUuid, repeatTime, intervalFrame);
		}
		else {
			auto renderInfo = PyObject_CallMethod(taskObject, "_cpp_getRenderInfo", NULL);
			auto enemyInfo = PyObject_CallMethod(taskObject, "_cpp_getEnemyInfo", NULL);

			const char* imagePath; int divideInfo[2]; float scaleInfo[3]; int sandByInfo[2]; int walkInfo[2]; int colorType;
			PyArg_ParseTuple(renderInfo, "s(ii)(fff)(ii)(ii)i", &imagePath, &divideInfo[0], &divideInfo[1], &scaleInfo[0], &scaleInfo[1], &scaleInfo[2],
				&sandByInfo[0], &sandByInfo[1], &walkInfo[0], &walkInfo[1], &colorType);

			float position[3], velocity, acceleration, angle, angleAcceleration, maxHealth;
			PyArg_ParseTuple(enemyInfo, "(fff)fffff", &position[0], &position[1], &position[2], &velocity, &acceleration, &angle, &angleAcceleration, &maxHealth);
			task = new TaskEnemy(uuid, targetUuid, repeatTime, intervalFrame, imagePath, glm::vec2(divideInfo[0], divideInfo[1]),
				glm::vec3(scaleInfo[0], scaleInfo[1], scaleInfo[2]), glm::vec2(sandByInfo[0], sandByInfo[1]), glm::vec2(walkInfo[0], walkInfo[1]),
				glm::vec3(position[0], position[1], position[2]), velocity, acceleration, angle, angleAcceleration, colorType, maxHealth);
		}
		
		int unitSize;
		PyArg_Parse(sizeInfo, "i", &unitSize);
		for (int i = 0; i < unitSize;i++) {
			PyObject *pUnit,*unitObj = PyObject_CallMethod(taskObject, "_cpp_getUnitItem", NULL);
			PyArg_Parse(unitObj, "O", &pUnit);

			TaskInsideUnit *unit = parseTaskUnitFromObject(uuid, pUnit);
			if (unit!=nullptr) {
				task->addSubUnit(unit);
			}
		}

	}
	return task;
}
