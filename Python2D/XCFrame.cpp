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

	XCFrameInfo::FrameRight = absWidth;
	XCFrameInfo::FrameLeft = -absWidth;
	XCFrameInfo::FrameTop = absHeight;
	XCFrameInfo::FrameBottom = -absHeight;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//OpenGL 4.3 Core Mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式牛 逼
	glfwWindowHint(GLFW_RESIZABLE, info.winResize);//No resizable.
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, info.winScale);//Auto change size
	
	pscreen = glfwCreateWindow(FrameWidth, FrameHeight, info.winTitle.c_str(), nullptr, nullptr);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(pscreen, (mode->width - FrameWidth) / 2, (mode->height - FrameHeight) / 2);
	if (pscreen == nullptr) {
		MessageBox(NULL, "无法创建窗口！", "ERROR", MB_ICONERROR);
		exit(-1);
	}
	glfwMakeContextCurrent(pscreen);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(pscreen, FrameResize);
	glfwSetWindowPosCallback(pscreen, FramePos);
	gl3wInit();

	AudioHelper::EvonInit();
}
void XCFrame::FrameLoop()
{	
	while (!glfwWindowShouldClose(pscreen)) {
		TaskManager::getInstance()->TaskWork();
		RenderManager::getInstance()->RenderWork();

		glfwSwapBuffers(pscreen);
		glfwPollEvents();
	}
	glfwDestroyWindow(pscreen);
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