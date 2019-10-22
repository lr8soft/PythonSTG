#pragma once
#ifndef _XCSTAGE_H
#define _XCSTAGE_H_
#include <Python.h>
#include <GL/glcorearb.h>
#include <string>
#include <list>
#include <atomic>
#include "../Task/Task.h"
#include "../../util/GameTimer.h"
#include "../Background/BackgroundHelper.h"
class Stage {
private:
	int stageBackgroundID = 0;
	Background* stageBackground;

	std::string stageUuid;
	std::list<Task*> stageTaskGroup;

	XCGameTimer timer;
	PyObject* itemStage;
	bool stageFinish = false;
	bool isStageInit = false;
public:
	Stage() = delete;
	Stage(std::string uuid, PyObject* item);
	void addTask(Task* pTask);
	void stageInit();
	void stageWork();
	void stageRelease();
	bool getStageInit();
	bool getStageFinish();
	std::string getUuid();
	Background* getBackgroundPointer();

};
#endif