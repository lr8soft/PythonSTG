#pragma once
#ifndef _XCFRAME_H_
#define _XCFRAME_H_
#include <GLFW/glfw3.h>
#include "util/GameTimer.h"
#include "XCInterpreter/XCInterpreter.h"
class XCFrame {
private:
	GLFWwindow* pscreen;
	XCInterpreter *interpreter;
	XCGameTimer timer;

	static void FrameResize(GLFWwindow* screen, int w, int h);
	static int FrameWidth, FrameHeight;
public:
	void FrameInit();
	void FrameLoop();
	void FrameFinalize();
};
#endif // !_XCFRAME_H_
