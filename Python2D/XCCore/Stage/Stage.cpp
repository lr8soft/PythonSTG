#include "Stage.h"
#include "../../XCInterpreter/ScriptLoader.h"
#include "../XCRender/XCImageHelper.h"
#include "../Item/Player.h"

#include "../Task/TaskHelper.h"
#include "../Bullet/BulletHelper.h"
#include <GL3/gl3w.h>
GLenum Stage::parseAlphaFunc(int src)
{
	switch (src)
	{
	case 0:
		return GL_NONE;
	case 1:
		return GL_ONE_MINUS_SRC_ALPHA;
	default:
		return GL_NONE;
	}
}
GLenum Stage::parseColorFunc(int src)
{
	switch (src)
	{
	case 0:
		return GL_NONE;
	case 1:
		return GL_ONE_MINUS_SRC_COLOR;
	default:
		return GL_NONE;
	}
}
Stage::Stage(std::string uuid, PyObject* item)
{
	itemStage = item;
	stageUuid = uuid;
}

void Stage::stageInit()
{
	if (!getStageInit()) {
		MultiThreadDefine
		PyObject* taskSizeObj = PyObject_CallMethod(itemStage, "_cpp_getTaskSize", NULL);
		int taskSize = ScriptLoader::getSingleArg<int>(taskSizeObj);
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

		MultiThreadDefineEnd
		isStageInit = true;
	}
}

void Stage::stageWork()
{
	timer.Tick();
	std::vector<Task*>::iterator stageBegin = stageTaskGroup.begin();
	std::vector<Task*>::iterator stageEnd = stageTaskGroup.end();
	for (auto task = stageBegin; task != stageEnd; task++) {
		if (!(*task)->getTaskInit())
			(*task)->TaskInit();

		if(!(*task)->getTaskFinish())
			(*task)->TaskWork();
		else {
			(*task)->TaskRelease();
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
}

void Stage::stageRelease()
{
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
