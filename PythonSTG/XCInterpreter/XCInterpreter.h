#pragma once
#ifndef _XCINTERPRETER_H_
#define _XCINTERPRETER_H_
#include "ScriptLoader.h"
#include <memory>
#include <map>
#include <mutex>
struct InitInfo {
	std::string winTitle;
};
class XCInterpreter {
private:
	ScriptLoader pyLoader;
	PyObject* scriptCore;
	InitInfo* InterpreterThread();

	static InitInfo* gameInitInfo;

	void parseStageItem();
	void parsePlayerEntity();
public:
	XCInterpreter();
	~XCInterpreter();
	InitInfo* getInitInfo();
	void loadTaskManagerInfo();
};

#endif