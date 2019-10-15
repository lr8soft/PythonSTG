#pragma once
#ifndef _XCFRAME_H_
#define _XCFRAME_H_
#include <GLFW/glfw3.h>
#include "XCInterpreter/XCInterpreter.h"
#include "util/GameTimer.h"
class XCFrame {
private:
	GLFWwindow* pscreen;
	static XCFrame* pInstance;
	static XCInterpreter *interpreter;
	static int FrameWidth, FrameHeight;
	static void FrameResize(GLFWwindow* screen, int w, int h);
	static void FramePos(GLFWwindow* screen, int x, int y);

	XCGameTimer timer;
	XCFrame();
public:
	GLFWwindow* getScreen();
	static XCFrame* getInstance();
	
	void FrameInit();
	void FrameLoop();
	void FrameFinalize();
};
#endif // !_XCFRAME_H_
