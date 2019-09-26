#pragma once
#ifndef _XCINTERPRETER_H_
#define _XCINTERPRETER_H_
#include "ScriptLoader.h"
#include <GLFW/glfw3.h>
#include <memory>
#include <map>
#include <mutex>
class XCInterpreter {
	friend void pythonKeyFuncCallBack(GLFWwindow* p, int key, int scancode, int action, int mods);
private:
	GLFWwindow* pScreen;
	ScriptLoader pyLoader;
	PyObject* scriptCore;
	static PyObject* keyCallback;
	bool shouldThreadEnd = false;
	void InterpreterThread();
	std::mutex threadMutex;
	void setThreadEnd(bool isEnd);
	bool getThreadEnd();

	void parseDynamicRenderItem();
	void parseStaticRenderItem();
	
public:
	XCInterpreter(GLFWwindow* pwin);
	~XCInterpreter();
	void ScriptLaunch();
};

#endif