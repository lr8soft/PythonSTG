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

		int waitFrame, repeatTime;
		PyArg_ParseTuple(unitDetailInfo, "ii", &waitFrame, &repeatTime);

		unit = new TaskInsideUnit(uuid, waitFrame, repeatTime);//R  E  L  E  A  S  E     P  L  E  A S  E
		
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
		auto targetInfo = PyObject_CallMethod(taskObject, "_cpp_getTargetUuidSize", NULL);
	

		const char *uuid; int  repeatTime, intervalFrame, waitFrame, isEnemyTask = 0;
		PyArg_ParseTuple(taskInfo, "siii|p", &uuid, &repeatTime, &intervalFrame, &waitFrame, &isEnemyTask);

		int targetUuidSize;
		PyArg_Parse(targetInfo, "i", &targetUuidSize);

		std::vector<std::string> targetUuid;
		if (targetUuidSize > 0){
			for (int i = 0; i < targetUuidSize; i++) {
				const char* tuuid;
				auto targetInfo = PyObject_CallMethod(taskObject, "_cpp_getTargetUuidSingle", NULL);
				PyArg_Parse(targetInfo, "s", &tuuid);
				targetUuid.push_back(tuuid);
			}
		}

		if (!isEnemyTask) {
			task = new Task(uuid, targetUuid, repeatTime, intervalFrame, waitFrame);
		}
		else {
			auto renderInfo = PyObject_CallMethod(taskObject, "_cpp_getRenderInfo", NULL);
			auto enemyInfo = PyObject_CallMethod(taskObject, "_cpp_getEnemyInfo", NULL);
			auto dropInfo = PyObject_CallMethod(taskObject, "_cpp_getDropItemSize", NULL);//_cpp_getDropItemSize;

			int dropItemSize = 0;
			PyArg_Parse(dropInfo, "i", &dropItemSize);

			if (dropItemSize > 0) {
				for (int i = 0; i < dropItemSize; i++) {
					auto dropItem = PyObject_CallMethod(taskObject, "_cpp_getDropItem", NULL);
					int type, count;
					PyArg_ParseTuple(dropItem, "ii", &type, &count);
				}
			}

			const char* imagePath; int divideInfo[2]; float scaleInfo[3]; int sandByInfo[2]; int walkInfo[2]; int colorType;
			PyArg_ParseTuple(renderInfo, "s(ii)(fff)(ii)(ii)i", &imagePath, &divideInfo[0], &divideInfo[1], &scaleInfo[0], &scaleInfo[1], &scaleInfo[2],
				&sandByInfo[0], &sandByInfo[1], &walkInfo[0], &walkInfo[1], &colorType);

			float position[3], velocity, movingTime,acceleration, angle, angleAcceleration, maxHealth;
			PyArg_ParseTuple(enemyInfo, "(fff)ffffff", &position[0], &position[1], &position[2], &velocity, &movingTime, &acceleration, &angle, &angleAcceleration, &maxHealth);
			task = new TaskEnemy(uuid, targetUuid, repeatTime, intervalFrame, waitFrame,imagePath, glm::vec2(divideInfo[0], divideInfo[1]),
				glm::vec3(scaleInfo[0], scaleInfo[1], scaleInfo[2]), glm::vec2(sandByInfo[0], sandByInfo[1]), glm::vec2(walkInfo[0], walkInfo[1]),
				glm::vec3(position[0], position[1], position[2]), velocity, movingTime, acceleration, angle, angleAcceleration, colorType, maxHealth);
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
