#include <sstream>
#include <GL3/gl3w.h>
#include "XCFrame.h"
#include "XCCore/XCAudio/AudioHelper.h"
#include "XCCore/Task/TaskManager.h"
#include "XCCore/XCRender/RenderManager.h"
#include "XCFrameInfo.h"
#include "util/ConfigManager.h"
XCFrame* XCFrame::pInstance = nullptr;
int XCFrame::FrameWidth, XCFrame::FrameHeight;

XCInterpreter *XCFrame::interpreter = nullptr;
void XCFrame::FrameInit()
{
	ScriptLoader::initPythonEvon();
	interpreter = new XCInterpreter;
	InitInfo info = interpreter->ScriptLaunch();
	FrameWidth = info.winWidth;
	FrameHeight = info.winHeight;
	XCFrameInfo::ScreenHeight = info.winHeight;
	XCFrameInfo::ScreenWidth = info.winWidth;

	float smallSize = FrameWidth > FrameHeight ? FrameHeight : FrameWidth;
	float absWidth = smallSize / (float)FrameWidth;
	float absHeight = smallSize / (float)FrameHeight;

	XCFrameInfo::ScreenOriginTitle = info.winTitle;
	XCFrameInfo::FrameRight = absWidth;
	XCFrameInfo::FrameLeft = -absWidth;
	XCFrameInfo::FrameTop = absHeight;
	XCFrameInfo::FrameBottom = -absHeight;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//OpenGL 4.3 Core Mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//ºËÐÄÄ£Ê½Å£ ±Æ
	glfwWindowHint(GLFW_RESIZABLE, info.winResize);//No resizable.
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, info.winScale);//Auto change size

	GLFWmonitor* primaryMonitor = info.winFullScreen ? glfwGetPrimaryMonitor() : nullptr;
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	tscreen = glfwCreateWindow(1, 1, "ThreadInitHelper", nullptr, nullptr);
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
	pscreen = glfwCreateWindow(FrameWidth, FrameHeight, XCFrameInfo::ScreenOriginTitle.c_str(), primaryMonitor, tscreen);
	glfwMakeContextCurrent(pscreen);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(pscreen, (mode->width - FrameWidth) / 2, (mode->height - FrameHeight) / 2);
	if (pscreen == nullptr) {
		std::cerr << "[ERROR] Failed to create window!\n";
		exit(-1);
	}
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(pscreen, FrameResize);
	glfwSetWindowPosCallback(pscreen, FramePos);
	gl3wInit();

	AudioHelper::EvonInit();
}
void XCFrame::FrameLoop()
{	
	while (!glfwWindowShouldClose(pscreen)) {
		timer.Tick();
		TaskManager::getInstance()->TaskWork();
		RenderManager::getInstance()->RenderWork();

		glfwSwapBuffers(pscreen);
		glfwPollEvents();
		glfwSetWindowTitle(pscreen, 
			(XCFrameInfo::ScreenOriginTitle + "  | RenderObject: " + std::to_string(RenderManager::getInstance()->GetRenderObjectCount())
				+  "  FPS: "+std::to_string(timer.getFramePerSecond())).c_str());
	}
	isFrameTerminate = true;
	glfwDestroyWindow(pscreen);
	glfwDestroyWindow(tscreen);
	glfwTerminate();
}
void XCFrame::FrameFinalize()
{
	ScriptLoader::unloadPythonEvon();
	AudioHelper::UnloadEvon();
	delete pInstance;
}
void XCFrame::FrameResize(GLFWwindow * screen, int w, int h)
{
	if (w > 0 && h > 0) {
		glViewport(0, 0, w, h);
		FrameWidth = w;
		FrameHeight = h;

		float smallSize = FrameWidth > FrameHeight ? FrameHeight : FrameWidth;
		float absWidth = smallSize / (float)FrameWidth;
		float absHeight = smallSize / (float)FrameHeight;

		XCFrameInfo::FrameRight = absWidth;
		XCFrameInfo::FrameLeft = -absWidth;
		XCFrameInfo::FrameTop = absHeight;
		XCFrameInfo::FrameBottom = -absHeight;

		XCFrameInfo::ScreenHeight = h;
		XCFrameInfo::ScreenWidth = w;

	}
}

void XCFrame::FramePos(GLFWwindow * screen, int x, int y)
{
	
}

XCFrame * XCFrame::getInstance()
{
	if (pInstance==nullptr) {
		pInstance = new XCFrame;
	}
	return pInstance;
}

GLFWwindow * XCFrame::getScreen()
{
	return pscreen;
}
GLFWwindow * XCFrame::getThreadScreen()
{
	return tscreen;
}
bool XCFrame::getFrameTerminate()
{
	return isFrameTerminate;
}
XCFrame::XCFrame() {
	xcstd::ConfigManager cfg("p2d.cfg");
	if (cfg.IsFirstRun()) {
		cfg.AddNewInfo("p1_up", std::to_string(GLFW_KEY_UP));
		cfg.AddNewInfo("p1_down", std::to_string(GLFW_KEY_DOWN));
		cfg.AddNewInfo("p1_left", std::to_string(GLFW_KEY_LEFT));
		cfg.AddNewInfo("p1_right", std::to_string(GLFW_KEY_RIGHT));
		cfg.AddNewInfo("p1_shoot", std::to_string(GLFW_KEY_Z));
		cfg.AddNewInfo("p1_special", std::to_string(GLFW_KEY_X));
		cfg.AddNewInfo("p1_item", std::to_string(GLFW_KEY_C));
		cfg.AddNewInfo("p1_slow", std::to_string(GLFW_KEY_LEFT_SHIFT));
	}
	else {
		XCFrameInfo::p1_keyUp = atoi(cfg.GetValue("p1_up").c_str());
		XCFrameInfo::p1_keyDown = atoi(cfg.GetValue("p1_down").c_str());
		XCFrameInfo::p1_keyLeft = atoi(cfg.GetValue("p1_left").c_str());
		XCFrameInfo::p1_keyRight = atoi(cfg.GetValue("p1_right").c_str());
		XCFrameInfo::p1_keyShoot = atoi(cfg.GetValue("p1_shoot").c_str());
		XCFrameInfo::p1_keySlow = atoi(cfg.GetValue("p1_slow").c_str());
	}
}