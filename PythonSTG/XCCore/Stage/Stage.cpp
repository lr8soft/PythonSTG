#include "Stage.h"
#include "../../XCInterpreter/ScriptLoader.h"
#include "../XCRender/XCImageHelper.h"
#include "../Item/Player.h"

#include "../Task/TaskHelper.h"
#include "../Bullet/BulletHelper.h"
#include "../Boss/BossHelper.h"
#include <GL3/gl3w.h>
Stage::Stage(std::string uuid, PyObject* item)
{
	itemStage = item;
	stageUuid = uuid;
}

void Stage::addTask(Task * pTask)
{
	stageTaskGroup.push_back(pTask);
}

void Stage::stageInit()
{
	if (!isStageInit) {
		MultiThreadDefine
		PyObject* taskSizeObj = PyObject_CallMethod(itemStage, "_cpp_getTaskSize", NULL);
		PyObject* bossSizeObj = PyObject_CallMethod(itemStage, "_cpp_getBossSize", NULL);
		PyObject* backgroundIdObj = PyObject_CallMethod(itemStage, "_cpp_getBackground", NULL);
		int taskSize = ScriptLoader::getSingleArg<int>(taskSizeObj);
		int bossSize = ScriptLoader::getSingleArg<int>(bossSizeObj);
		stageBackgroundID = ScriptLoader::getSingleArg<int>(backgroundIdObj);
		if (taskSize > 0) {

			for (int i = 0; i < taskSize; i++) {
				PyObject *pItem, *itemObj = PyObject_CallMethod(itemStage, "_cpp_getTaskItem", NULL);
				PyArg_Parse(itemObj, "O", &pItem);
				
				Task* task = TaskHelper::parseTaskFromObject(pItem);
				if (task!=nullptr) {
					stageTaskGroup.push_back(task);
				}
			}
		}

		if (bossSize > 0) {
			for (int i = 0; i < bossSize; i++) {
				PyObject *pItem, *itemObj = PyObject_CallMethod(itemStage, "_cpp_getBossItem", NULL);
				PyArg_Parse(itemObj, "O", &pItem);

				Boss* boss = BossHelper::parseBossFromObject(pItem);
				if (boss != nullptr) {
					stageTaskGroup.push_back(boss);
				}
			}
		}
		MultiThreadDefineEnd
		stageBackground = BackgroundHelper::getBackgroundByID(stageBackgroundID);
		stageBackground->BackgroundInit();
		isStageInit = true;
	}
}

void Stage::stageWork()
{
	if (isStageInit) {
		timer.Tick();
		std::list<Task*>::iterator stageBegin = stageTaskGroup.begin();
		std::list<Task*>::iterator stageEnd = stageTaskGroup.end();
		bool allTaskWaitTarget = true;
		for (auto task = stageBegin; task != stageEnd; task++) {
			if (!(*task)->getTaskInit())
				(*task)->TaskInit();

			if (!(*task)->getTaskFinish()) {
				(*task)->TaskWork();
				if (!(*task)->getIsTaskWaitingForTarget()) {
					allTaskWaitTarget = false;
				}
			}


			if ((*task)->getTaskFinish()) {
				(*task)->TaskRelease();
				delete *task;
				if (std::next(task) == stageTaskGroup.end()) {
					stageTaskGroup.erase(task);
					break;
				}
				else {
					task = stageTaskGroup.erase(task);
					stageEnd = stageTaskGroup.end();
				}
			}
		}
		if (allTaskWaitTarget) {
			for (auto task = stageBegin; task != stageEnd; task++) {
				(*task)->TaskRelease();
				delete *task;
				if (std::next(task) == stageTaskGroup.end()) {
					stageTaskGroup.erase(task);
					break;
				}
				else {
					task = stageTaskGroup.erase(task);
					stageEnd = stageTaskGroup.end();
				}
			}
			stageTaskGroup.clear();
		}
		if (stageTaskGroup.empty()) {
			stageFinish = true;
		}
	}
}

void Stage::stageRelease()
{
	if (stageBackground != nullptr) {
		stageBackground->BackgroundRelease();
		delete stageBackground;
	}
}

bool Stage::getStageInit()
{
	return isStageInit;
}

bool Stage::getStageFinish()
{
	return stageFinish;
}

std::string Stage::getUuid()
{
	return stageUuid;
}

Background * Stage::getBackgroundPointer()
{
	return stageBackground;
}
