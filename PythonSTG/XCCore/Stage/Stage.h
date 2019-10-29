#pragma once
#ifndef _XCSTAGE_H
#define _XCSTAGE_H_
#include <Python.h>
#include <GL/glcorearb.h>
#include <string>
#include <list>
#include <map>
#include <atomic>
#include "../XCAudio/AudioHelper.h"
#include "../Task/Task.h"
#include "../../util/GameTimer.h"
#include "../Background/BackgroundHelper.h"
class Stage {
private:
	int stageBackgroundID = 0, stageRank = 2;
	Background* stageBackground;

	std::string stageUuid;
	std::map<std::string, Task*> stageTaskGroup;
	ALuint bgmBuffer = 0;

	XCGameTimer timer;
	PyObject* itemStage;
	bool stageFinish = false;
	bool isStageInit = false;
public:
	Stage() = delete;
	Stage(std::string uuid, PyObject* item);
	void addTask(Task* pTask);
	void removeTask(std::string &uuid);
	void setTaskInitCoord(std::string &uuid, float x, float y);

	void stageInit();
	void stageWork();
	void stageRelease();
	bool getStageInit();
	bool getStageFinish();
	std::string getUuid();
	Background* getBackgroundPointer();

};
#endif