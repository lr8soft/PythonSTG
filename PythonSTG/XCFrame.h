#pragma once
#ifndef _XCFRAME_H_
#define _XCFRAME_H_
#include <GLFW/glfw3.h>
#include <atomic>
#include "XCInterpreter/XCInterpreter.h"
#include "util/GameTimer.h"
class XCFrame {
private:
	const char* PythonSTGVersion = "v0.32_release_update3";
	std::atomic_bool isFrameTerminate = false;
	GLFWwindow* pscreen = nullptr, *tscreen = nullptr;
	static XCFrame* pInstance;
	static XCInterpreter *interpreter;
	static int FrameWidth, FrameHeight;
	static void FrameResize(GLFWwindow* screen, int w, int h);
	static void FramePos(GLFWwindow* screen, int x, int y);

	bool isFullScreen = false;

	XCGameTimer timer;
	XCFrame();

	GLFWimage* getApplicationIcon();
public:
	GLFWwindow* getScreen();
	GLFWwindow* getThreadScreen();
	bool getFrameTerminate();
	static XCFrame* getInstance();
	
	void FrameInit();
	void FrameLoop();
	void FrameFinalize();
};
#endif // !_XCFRAME_H_
