#pragma once
#ifndef _XCFRAME_H_
#define _XCFRAME_H_
#include <GLFW/glfw3.h>
#include "util/GameTimer.h"
#include "XCInterpreter/XCInterpreter.h"
class XCFrame {
private:
	GLFWwindow* pscreen;
	static XCFrame* pInstance;
	static XCInterpreter *interpreter;
	static void FrameResize(GLFWwindow* screen, int w, int h);
	XCFrame();
public:
	GLFWwindow* getScreen();
	static XCFrame* getInstance();
	static XCGameTimer timer;
	static int FrameWidth, FrameHeight;
	static float FrameLeft, FrameRight, FrameTop, FrameBottom;
	void FrameInit();
	void FrameLoop();
	void FrameFinalize();
};
#endif // !_XCFRAME_H_
