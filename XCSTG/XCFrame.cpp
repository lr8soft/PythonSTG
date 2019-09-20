#include <sstream>
#include <GL3/gl3w.h>
#include "XCFrame.h"
#include "XCInfo.h"
#include "XCCore/XCFont/XCFont.h"
#include "XCCore/XCRender/XCImageManager.h"
using namespace XCInfo;
int XCFrame::FrameWidth = defaultWidth;
int XCFrame::FrameHeight = defaultHeight;
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

}
void XCFrame::FrameLoop()
{	
	glfwMakeContextCurrent(pscreen);
	XCFont font;
	font.FontASCIIInit();
	font.FontSetWidthAndHeight(FrameHeight, FrameWidth);
	XCImageManager image("assets/123.png", true);
	interpreter.ScriptLaunch();
	while (!glfwWindowShouldClose(pscreen)) {
		timer.Tick();
		glClear(GL_COLOR_BUFFER_BIT);
		image.ImageRender(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f),glm::vec3(0.5f),
			image.GetSpecificTexture(3,3,0,0));
		font.FontASCIIRender(std::to_string(timer.getFPS()), 0.0, 0.0, 1.0, glm::vec4(0.1,0.1,0.6,1.0));
		glfwSwapBuffers(pscreen);
		glfwPollEvents();
	}
	interpreter.ScriptRelease();
}
void XCFrame::FrameFinalize()
{
}
void XCFrame::FrameResize(GLFWwindow * screen, int w, int h)
{
	FrameWidth = w;
	FrameHeight = h;
}
