#pragma once
#ifndef _XCINTERPRETER_H_
#define _XCINTERPRETER_H_
#include "..\..\util\ScriptLoader.h"
class XCInterpreter {
private:
	ScriptLoader pyLoader;
	PyObject* scriptCore;
public:
	XCInterpreter();
	void ScriptLaunch();
	void ScriptRelease();
};
#endif