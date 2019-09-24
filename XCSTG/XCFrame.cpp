#include <sstream>
#include <GL3/gl3w.h>
#include "XCFrame.h"
#include "XCInfo.h"
#include "XCCore/XCFont/XCFont.h"
#include "XCCore/XCRender/RenderManager.h"
using namespace XCInfo;
int XCFrame::FrameWidth = defaultWidth;
int XCFrame::FrameHeight = defaultHeight;
XCInterpreter *XCFrame::interpreter = nullptr;
void XCFrame::FrameInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//OpenGL 4.2 Core Mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式牛 逼
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//No resizable.
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);//Auto change size
	pscreen = glfwCreateWindow(FrameWidth, FrameHeight, frameTitle.c_str(), nullptr, nullptr);
	if (pscreen == nullptr) {
		MessageBox(NULL, "无法创建窗口！", "ERROR", MB_ICONERROR);
		exit(-1);
	}
	glfwMakeContextCurrent(pscreen);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(pscreen, FrameResize);
	gl3wInit();

	interpreter = new XCInterpreter(pscreen);
	interpreter->ScriptLaunch();
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

}
void XCFrame::FrameResize(GLFWwindow * screen, int w, int h)
{
	FrameWidth = w;
	FrameHeight = h;
}
