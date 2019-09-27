#include <sstream>
#include <GL3/gl3w.h>
#include "XCFrame.h"
#include "XCCore/XCFont/XCFont.h"
#include "XCCore/XCRender/RenderManager.h"
XCGameTimer XCFrame::timer;
int XCFrame::FrameWidth = 640, XCFrame::FrameHeight = 480;
float XCFrame::FrameBottom = -1.0f, XCFrame::FrameTop = 1.0f, XCFrame::FrameRight = 1.0f, XCFrame::FrameLeft = -1.0f;
XCInterpreter *XCFrame::interpreter = nullptr;
void XCFrame::FrameInit()
{
	ScriptLoader::initPythonEvon();
	interpreter = new XCInterpreter;
	InitInfo info = interpreter->ScriptLaunch();
	FrameWidth = info.winWidth;
	FrameHeight = info.winHeight;
	if (FrameWidth >= 640) {
		FrameRight = 640 * 1.0f / (float)FrameWidth;
		FrameLeft = -640 * 1.0f / (float)FrameWidth;
	}
	if (FrameHeight >= 480) {
		FrameTop = 480 * 1.0f / (float)FrameHeight;
		FrameBottom = -480 * 1.0f / (float)FrameHeight;
	}

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//OpenGL 4.2 Core Mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式牛 逼
	glfwWindowHint(GLFW_RESIZABLE, info.winResize);//No resizable.
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, info.winScale);//Auto change size
	pscreen = glfwCreateWindow(FrameWidth, FrameHeight, info.winTitle.c_str(), nullptr, nullptr);
	if (pscreen == nullptr) {
		MessageBox(NULL, "无法创建窗口！", "ERROR", MB_ICONERROR);
		exit(-1);
	}
	glfwMakeContextCurrent(pscreen);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(pscreen, FrameResize);
	gl3wInit();

	
}
void XCFrame::FrameLoop()
{	
	XCFont font;
	font.FontASCIIInit();
	font.FontSetWidthAndHeight(FrameHeight, FrameWidth);
	while (!glfwWindowShouldClose(pscreen)) {
		timer.Tick();
		glClear(GL_COLOR_BUFFER_BIT);
		font.FontASCIIRender(std::to_string(timer.getFPS()), 0.0, 0.0, 1.0, glm::vec4(0.1,0.1,0.6,1.0));

		RenderManager::getInstance()->RenderWork();
		glfwSwapBuffers(pscreen);
		glfwPollEvents();
	}
	
}
void XCFrame::FrameFinalize()
{
	ScriptLoader::unloadPythonEvon();
}
void XCFrame::FrameResize(GLFWwindow * screen, int w, int h)
{
	FrameWidth = w;
	FrameHeight = h;
	if (FrameWidth >= 640) {
		FrameRight = 640 * 1.0f / (float)FrameWidth;
		FrameLeft = -640 * 1.0f / (float)FrameWidth;
	}
	if (FrameHeight >= 480) {
		FrameTop = 480 * 1.0f / (float)FrameHeight;
		FrameBottom = -480 * 1.0f / (float)FrameHeight;
	}
	glViewport(0, 0, FrameWidth, FrameHeight);
}
