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
	std::string winTitle;
};
class XCInterpreter {
private:
	ScriptLoader pyLoader;
	PyObject* scriptCore;
	InitInfo InterpreterThread();

	void parseDynamicRenderItem();
	void parseStaticRenderItem();
	
public:
	XCInterpreter();
	~XCInterpreter();
	InitInfo ScriptLaunch();
};

#endif