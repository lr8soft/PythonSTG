#include "XCInterpreter.h"
#include <string>
#include <GLFW/glfw3.h>
using namespace std;
XCInterpreter::XCInterpreter(GLFWwindow* pwin)
{
	pScreen = pwin;
	PyScriptThread = new thread(&XCInterpreter::InterpreterThread, this);
}

void XCInterpreter::InterpreterThread()
{
	pyLoader.initPythonEvon();
	PyObject* mainScript = pyLoader.importModule("script.XCCore");
	pyLoader.callFunction(mainScript, "coreInitializer", NULL);

	PyObject* height = pyLoader.getAttrib(mainScript, "winHeight");
	PyObject* width = pyLoader.getAttrib(mainScript, "winWidth");
	PyObject* title = pyLoader.getAttrib(mainScript, "winTitle");
	
	//int h = pyLoader.getSingleArg<int>(height);
	//int w = pyLoader.getSingleArg<int>(width);
	const char* t = pyLoader.getSingleArg<const char*>(title);
	glfwSetWindowTitle(pScreen, t);
	//glfwSetWindowSize(pScreen, w, h);
	while (!getEnd()) {
		parseRenderItem(mainScript);
	}
	pyLoader.callFunction(mainScript, "coreFinalizer", NULL);
	pyLoader.unloadPythonEvon();
}
void XCInterpreter::parseRenderItem(PyObject * module)
{
	PyObject* renderItem = pyLoader.callFunction(module, "getRenderItem", NULL);
	PyObject* renderCountItem = pyLoader.callFunction(module, "getRenderItemCount", NULL);
	int itemSize = -1;
	std::string renderItemFormat = "(";
	PyArg_Parse(renderCountItem, "i", &itemSize);
	std::cout << itemSize << std::endl;
	for (int i = 0; i < itemSize;i++) {
		renderItemFormat += "(ssuoooo)";
	}
	renderItemFormat += ")";
	static const char *renderType, *imagePath;
	bool isFlexible = false; PyObject* renderPos, *colorValue, *scaleValue,* divideValue;

	PyArg_Parse(renderItem, renderItemFormat.c_str(), &renderType, &imagePath,&isFlexible, &renderPos,&colorValue,&scaleValue,&divideValue);
//	std::cout << renderType << " "<<imagePath << std::endl;
}
void XCInterpreter::ScriptLaunch()
{
	std::cout << "[INFO] Now pyInterpreter detach." << std::endl;
	PyScriptThread->detach();
}

XCInterpreter::~XCInterpreter()
{
	setEnd(true);
	delete PyScriptThread;
}

