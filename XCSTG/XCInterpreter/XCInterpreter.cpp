#include "XCInterpreter.h"
#include "..\XCCore\XCRender\RenderManager.h"
#include <string>
#include <GLFW/glfw3.h>
#include <thread>

using namespace std;
XCInterpreter::XCInterpreter(GLFWwindow* pwin)
{
	pScreen = pwin;
	
}

void XCInterpreter::InterpreterThread()
{
	MultiThreadDefine
	PyObject* mainScript = pyLoader.importModule("script.XCCore");
	pyLoader.callObjectMethod(mainScript, "coreInitializer", NULL);

	PyObject* height = pyLoader.getAttrib(mainScript, "winHeight");
	PyObject* width = pyLoader.getAttrib(mainScript, "winWidth");
	PyObject* title = pyLoader.getAttrib(mainScript, "winTitle");



	
	//int h = pyLoader.getSingleArg<int>(height);
	//int w = pyLoader.getSingleArg<int>(width);
	//glfwSetWindowSize(pScreen, w, h);
	const char* t = pyLoader.getSingleArg<const char*>(title);
	glfwSetWindowTitle(pScreen, t);
	MultiThreadDefineEnd

	while (true) {
		MultiThreadDefine
		parseDynamicRenderItem();
		parseStaticRenderItem();
		MultiThreadDefineEnd
	}
	

}
;
void XCInterpreter::parseDynamicRenderItem()
{
	PyObject * module = pyLoader.importModule("script.XCRender");
	PyObject* renderCountItem = pyLoader.callObjectMethod(module, "getInitDynamicRenderItemSize", NULL);
	
	int itemSize = 0;
	PyArg_Parse(renderCountItem, "i", &itemSize);
	if (itemSize>0) {
		for (int i = 0; i < itemSize; i++) {
			PyObject *pObject;
			PyObject *retValue = pyLoader.callObjectMethod(module, "getInitDynamicRenderItem", NULL);
			PyArg_Parse(retValue, "O", &pObject);

			if (pObject!=nullptr) {
				DynamicRenderItem item;
				item.item = new XCItemTransport(pObject);
				auto renderQueue = RenderManager::getInstance();
				renderQueue->AddDynamicWork(item);
#ifndef _DEBUG
				Py_INCREF(retValue);
#else
				Py_IncRef(retValue);
#endif

			}
		}
	}
}

void XCInterpreter::parseStaticRenderItem()
{
	PyObject * module = pyLoader.importModule("script.XCRender");
	PyObject* renderCountItem = pyLoader.callObjectMethod(module, "getStaticRenderSize", NULL);
	int itemSize = 0;
	PyArg_Parse(renderCountItem, "i", &itemSize);
	if (itemSize > 0) {
		for (int i = 0; i < itemSize; i++) { 
			const char *renderType, *imagePath; 
			float renderX = 0.0f, renderY = 0.0f, renderZ = 0.0f, scaleX = 0.0f, scaleY = 0.0f, scaleZ = 0.0f;
			float colorR = 0, colorG = 0, colorB = 0, colorA = 0;
			int divideColumn = 0, divideRow = 0, divideSelectCol = 0, divideSelectRow = 0, isFlexibleObj = 0;
			PyObject* renderItem = pyLoader.callObjectMethod(module, "getStaticRenderItem", NULL);
			PyArg_ParseTuple(
				renderItem,"ssp(fff)(ffff)(fff)(iiii)", 
				&renderType, &imagePath, &isFlexibleObj,
				&renderX, &renderY, &renderZ,
				&colorR, &colorG, &colorB, &colorA,
				&scaleX, &scaleY, &scaleZ,
				&divideColumn, &divideRow, &divideSelectCol, &divideSelectRow
			);
			bool isFlexible = isFlexibleObj;

			StaticRenderItem item;
			item.imagePath = imagePath;
			item.renderType = renderType;
			item.renderColor = glm::vec4(colorR,colorG,colorB,colorA);
			item.renderPos = glm::vec3(renderX, renderY, renderZ);
			item.scaleSize = glm::vec3(scaleX, scaleY, scaleZ);
			item.flexible = isFlexible;
			item.divideInfo[0] = divideColumn;
			item.divideInfo[1] = divideRow;
			item.divideInfo[2] = divideSelectCol;
			item.divideInfo[3] = divideSelectRow;

			auto renderQueue = RenderManager::getInstance();
			renderQueue->AddStaticWork(item);
#ifndef _DEBUG
			Py_DECREF(renderItem);
#else
			std::cout << "=======STATIC RENDER ITEM====="<<std::endl;
			std::cout << "TYPE:"<< renderType << " " << imagePath << " FX:"<<std::boolalpha <<isFlexible << std::endl;
			std::cout <<"RenderPos:"<< renderX << " " << renderY << " " << renderZ << std::endl;
			std::cout << "RGBA:" << colorR << " " << colorG << " " << colorB << " " << colorA << std::endl;
			std::cout <<"Scale:"<< scaleX << " " << scaleY << " " << scaleZ <<std::endl;
			std::cout << "DivideFormat:" << divideColumn << " " << divideRow << " " << divideSelectCol << " " << divideSelectRow << std::endl;
			std::cout << "===============================\n" << std::endl;
#endif
		}
	}
}
void XCInterpreter::ScriptLaunch()
{
	std::cout << "[INFO] Now pyInterpreter detach." << std::endl;
	thread PyScriptThread(&XCInterpreter::InterpreterThread, this);

	PyScriptThread.detach();
}
void XCInterpreter::setThreadEnd(bool isEnd)
{
	threadMutex.lock();
	shouldThreadEnd = isEnd;
	threadMutex.unlock();
}
bool XCInterpreter::getThreadEnd()
{
	bool shouldEnd = false;
	threadMutex.lock();
	shouldEnd = shouldThreadEnd;
	threadMutex.unlock();
	return shouldEnd;
}
XCInterpreter::~XCInterpreter()
{

}

