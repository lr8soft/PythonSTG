#pragma once
#ifndef _XCSTAGE_H
#define _XCSTAGE_H_
#include <Python.h>
#include <GL/glcorearb.h>
#include <string>
#include <vector>
#include "../XCItem/XCItem.h"
#include "../../util/GameTimer.h"
struct itemStruct {
	XCItem* item;
	bool useBlend;
	GLenum colorFunc;
	GLenum alphaFunc;
};
class XCStage {
private:
	std::string stageUuid;
	std::vector<itemStruct> stageItemGroup;

	XCGameTimer timer;
	PyObject* itemStage;
	bool stageFinish = false, isStageInit = false;
	GLenum parseAlphaFunc(int src);
	GLenum parseColorFunc(int src);
public:
	XCStage() = delete;
	XCStage(std::string uuid, PyObject* item);
	void stageInit();
	void stageWork();
	void stageRelease();
	bool getStageInit();
	bool getStageFinish();
	std::string getUuid();

};
#endif