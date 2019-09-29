#pragma once
#ifndef _XCSTAGE_H
#define _XCSTAGE_H_
#include <Python.h>
#include <GL/glcorearb.h>
#include <string>
#include <vector>
#include "../Item/Item.h"
#include "../Bullet/Bullet.h"
#include "../../util/GameTimer.h"
struct itemStruct {
	Item* item;
	bool useBlend;
	GLenum colorFunc;
	GLenum alphaFunc;
};
class Stage {
private:
	std::string stageUuid;
	std::vector<itemStruct> stageItemGroup;
	std::vector<Bullet*> stageBulletGroup;

	XCGameTimer timer;
	PyObject* itemStage;
	bool stageFinish = false, isStageInit = false;
	GLenum parseAlphaFunc(int src);
	GLenum parseColorFunc(int src);
public:
	Stage() = delete;
	Stage(std::string uuid, PyObject* item);
	void stageInit();
	void stageWork();
	void stageRelease();
	bool getStageInit();
	bool getStageFinish();
	std::string getUuid();

};
#endif