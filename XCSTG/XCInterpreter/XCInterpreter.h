#pragma once
#ifndef _XCINTERPRETER_H_
#define _XCINTERPRETER_H_
#include "ScriptLoader.h"
#include <GLFW/glfw3.h>

#include <map>
#include <mutex>
class XCInterpreter {
private:
	GLFWwindow* pScreen;
	ScriptLoader pyLoader;
	PyObject* scriptCore;
	bool shouldThreadEnd = false;
	void InterpreterThread();
	std::mutex threadMutex;
	void setThreadEnd(bool isEnd);
	bool getThreadEnd();
	void parseStaticRenderItem();
public:
	XCInterpreter(GLFWwindow* pwin);
	~XCInterpreter();
	void ScriptLaunch();
};
#endif