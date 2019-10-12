#include "TaskHelper.h"
#include "../Bullet/BulletHelper.h"
TaskInsideUnit * TaskHelper::parseTaskUnitFromObject(std::string uuid, PyObject * unitObject)
{
	TaskInsideUnit* unit  = nullptr;
	if (unitObject != nullptr) {
		auto unitSizeInfo = PyObject_CallMethod(unitObject, "_cpp_getBulletSize", NULL);
		auto unitDetailInfo = PyObject_CallMethod(unitObject, "_cpp_getUnitInfo", NULL);

		int unitSize;
		PyArg_Parse(unitSizeInfo, "i", &unitSize);

		int waitFrame, workInterval, repeatTime;
		PyArg_ParseTuple(unitDetailInfo, "iii", &waitFrame, &workInterval, &repeatTime); 
		unit = new TaskInsideUnit(uuid, waitFrame, workInterval, repeatTime);//R  E  L  E  A  S  E     P  L  E  A S  E

		if (unitSize>0) {
			for (int i = 0; i < unitSize;i++) {
				PyObject* pBullet, *bulletObject = PyObject_CallMethod(unitObject, "_cpp_getBulletItem", NULL);
				PyArg_Parse(bulletObject, "O", &pBullet);

				Bullet* bulletItem = BulletHelper::parseBulletObject(pBullet);
				if (bulletItem !=nullptr) {
					unit->addBullet(bulletItem);
				}
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

		const char *uuid, *targetUuid; int repeatTime, intervalFrame;
		PyArg_ParseTuple(taskInfo, "ssii", &uuid, &targetUuid, &repeatTime, &intervalFrame);
		task = new Task(uuid, targetUuid, repeatTime, intervalFrame);

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
