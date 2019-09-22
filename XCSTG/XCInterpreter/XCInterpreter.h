#pragma once
#ifndef _XCINTERPRETER_H_
#define _XCINTERPRETER_H_
#include "ScriptLoader.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <map>
#include <mutex>
class XCInterpreter {
private:
	std::thread *PyScriptThread;
	GLFWwindow* pScreen;
	ScriptLoader pyLoader;
	PyObject* scriptCore;
	bool shouldThreadEnd = false;
	void InterpreterThread();
	std::mutex threadMutex;
	inline void setEnd(bool isEnd) {
		threadMutex.lock();
		shouldThreadEnd = isEnd;
		threadMutex.unlock();
	}
	inline bool getEnd() {
		bool shouldEnd = false;
		threadMutex.lock();
		shouldEnd = shouldThreadEnd;
		threadMutex.unlock();
		return shouldEnd;
	}
	void parseRenderItem(PyObject* module);
public:
	XCInterpreter(GLFWwindow* pwin);
	~XCInterpreter();
	void ScriptLaunch();
};
#endif