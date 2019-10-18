#pragma once
#ifndef _XCINTERPRETER_H_
#define _XCINTERPRETER_H_
#include "ScriptLoader.h"
#include <memory>
#include <map>
#include <mutex>
struct InitInfo {
	int winHeight;
	int winWidth;
	bool winResize;
	bool winScale;
	bool winFullScreen;
	std::string winImage;
	std::string winTitle;
};
class XCInterpreter {
private:
	ScriptLoader pyLoader;
	PyObject* scriptCore;
	InitInfo InterpreterThread();

	void parseStageItem();
	void parsePlayerEntity();
public:
	XCInterpreter();
	~XCInterpreter();
	InitInfo getInitInfo();
	void loadTaskManagerInfo();
};

#endif