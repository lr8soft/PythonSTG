#include "XCInterpreter.h"
#include "..\XCCore\XCRender\RenderManager.h"
#include <string>
#include <chrono>
#include <future>
using namespace std;
XCInterpreter::XCInterpreter()
{

	
}
InitInfo XCInterpreter::InterpreterThread()
{
	InitInfo info;
	MultiThreadDefine
	PyObject* mainScript = pyLoader.importModule("script.XCCore");
	pyLoader.callObjectMethod(mainScript, "coreInitializer", NULL);

	PyObject* height = pyLoader.getAttrib(mainScript, "winHeight");
	PyObject* width = pyLoader.getAttrib(mainScript, "winWidth");
	PyObject* title = pyLoader.getAttrib(mainScript, "winTitle");
	PyObject* resize = pyLoader.getAttrib(mainScript, "winResize");
	PyObject* scale  = pyLoader.getAttrib(mainScript, "winScaleToMonitor");
	info.winHeight = pyLoader.getSingleArg<int>(height);
	info.winWidth = pyLoader.getSingleArg<int>(width);
	info.winTitle = pyLoader.getSingleArg<const char*>(title);

	int intValue;
	PyArg_Parse(resize, "p", &intValue);
	info.winResize = intValue;
	PyArg_Parse(scale, "p", &intValue);
	info.winScale = intValue;
#ifdef _DEBUG
	std::cout << "=======INIT INFO=======" << std::endl;
	std::cout << "width:" << info.winWidth << " height:" << info.winHeight << std::endl;
	std::cout << "resize:" << std::boolalpha << info.winResize << " scale:" << info.winScale << std::endl;
	std::cout << "title:" << info.winTitle << std::endl;
	std::cout << "=====================" << std::endl;
#endif


	//parseDynamicRenderItem();
	parseStaticRenderItem();
	MultiThreadDefineEnd
	return info;
}
;
void XCInterpreter::parseDynamicRenderItem()
{
	PyObject * module = pyLoader.importModule("script.XCInit");
	PyObject* renderCountItem = pyLoader.callObjectMethod(module, "getInitItemSize", NULL);
	
	int itemSize = 0;
	PyArg_Parse(renderCountItem, "i", &itemSize);
	if (itemSize>0) {
		for (int i = 0; i < itemSize; i++) {
			PyObject *pObject;
			PyObject *retValue = pyLoader.callObjectMethod(module, "getInitItem", NULL);
			PyArg_Parse(retValue, "O", &pObject);

			if (pObject!=nullptr) {
	//			DynamicRenderItem item;
	//			item.item = new XCItemTransport(pObject);
	//			auto renderQueue = RenderManager::getInstance();
	//			renderQueue->AddDynamicWork(item);
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
	PyObject * module = pyLoader.importModule("script.XCInit");
	PyObject* renderCountItem = pyLoader.callObjectMethod(module, "getStaticRenderSize", NULL);
	int itemSize = 0;
	PyArg_Parse(renderCountItem, "i", &itemSize);
	if (itemSize > 0) {
		for (int i = 0; i < itemSize; i++) { 
			const char *renderType, *imagePath; 
			float renderX = 0.0f, renderY = 0.0f, renderZ = 0.0f, scaleX = 0.0f, scaleY = 0.0f, scaleZ = 0.0f, rotateAngle = 0.0f;
			float colorR = 0, colorG = 0, colorB = 0, colorA = 0;
			int divideColumn = 0, divideRow = 0, divideSelectCol = 0, divideSelectRow = 0, isFlexibleObj = 0;
			int rotateWorkX = 0, rotateWorkY = 0, rotateWorkZ = 0;
			PyObject* pObject = pyLoader.callObjectMethod(module, "getStaticRenderItem", NULL);
			PyObject* renderItem = PyObject_CallMethod(pObject, "translate", NULL);
			PyArg_ParseTuple(
				renderItem,"ssp(fff)(ffff)(fff)(iiii)", 
				&renderType, &imagePath, &isFlexibleObj,
				&renderX, &renderY, &renderZ,
				&colorR, &colorG, &colorB, &colorA,
				&scaleX, &scaleY, &scaleZ,
				&divideColumn, &divideRow, &divideSelectCol, &divideSelectRow
			);
			bool isFlexible = isFlexibleObj ? true : false;

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

InitInfo XCInterpreter::ScriptLaunch()
{
	std::cout << "[INFO] Now pyInterpreter start." << std::endl;
	std::future<InitInfo> retFuture = std::async(&XCInterpreter::InterpreterThread, this);
	return retFuture.get();
}
XCInterpreter::~XCInterpreter()
{

}

