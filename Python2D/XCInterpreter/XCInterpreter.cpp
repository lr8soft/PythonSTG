#include "XCInterpreter.h"
#include "../XCCore/Task/TaskManager.h"
#include "../XCCore/Stage/Stage.h"
#include "../XCCore/Item/Player.h"
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
	//PyObject* image = pyLoader.getAttrib(mainScript, "winImage");
	info.winHeight = pyLoader.getSingleArg<int>(height);
	info.winWidth = pyLoader.getSingleArg<int>(width);
	info.winTitle = pyLoader.getSingleArg<const char*>(title);
	//info.winImage = pyLoader.getSingleArg<const char*>(image);

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
	std::cout << "=====================" << std::endl << std::endl;
#endif
	
	parseStageItem();
	parsePlayerEntity();
	MultiThreadDefineEnd
	return info;
}

void XCInterpreter::parseStageItem()
{
	PyObject * module = pyLoader.importModule("script.XCInit");
	PyObject* renderCountItem = pyLoader.callObjectMethod(module, "getStageItemSize", NULL);
	
	int itemSize = 0;
	PyArg_Parse(renderCountItem, "i", &itemSize);
	if (itemSize>0) {
		for (int i = 0; i < itemSize; i++) {
			PyObject *pObject;
			PyObject *retValue = pyLoader.callObjectMethod(module, "getStageItem", NULL);
			PyArg_Parse(retValue, "O", &pObject);
			
			if (pObject!=nullptr) {
				const char* uuid;
				PyObject *uuidValue = pyLoader.callObjectMethod(pObject, "_cpp_getUuid", NULL);
				PyArg_Parse(uuidValue, "s", &uuid);

				Stage *stage = new Stage(uuid, pObject);
				auto renderQueue = TaskManager::getInstance();
				renderQueue->AddStageItem(stage);
#ifndef _DEBUG
				//Py_INCREF(retValue);
#else
				std::cout << "Stage Uuid:"<< uuid <<  std::endl;
				//Py_IncRef(retValue);
#endif

			}
		}
	}
}


void XCInterpreter::parsePlayerEntity()
{
	PyObject * module = pyLoader.importModule("script.XCInit");
	PyObject* renderCountItem = pyLoader.callObjectMethod(module, "getPlayerItemSize", NULL);

	int itemSize = 0;
	PyArg_Parse(renderCountItem, "i", &itemSize);
	if (itemSize > 0) {
		for (int i = 0; i < itemSize; i++) {
			PyObject *pObject;
			PyObject *retValue = pyLoader.callObjectMethod(module, "getPlayerItem", NULL);
			PyArg_Parse(retValue, "O", &pObject);

			if (pObject != nullptr) {
				PyObject* imageData = PyObject_CallMethod(pObject, "_cpp_getInitRenderInfo", NULL);
				PyObject* playerData = PyObject_CallMethod(pObject, "_cpp_getPlayerData", NULL);
				PyObject* uuidData = PyObject_CallMethod(pObject, "_cpp_getUUID", NULL);

				const char* imagePath;
				float scaleX, scaleY, scaleZ;
				int imageCol, imageRow, standByRow, turnLeftRow, turnRightRow;
				PyArg_ParseTuple(imageData, "s(ii)(fff)(iii)", &imagePath, &imageCol, &imageRow, &scaleX, &scaleY, &scaleZ,&standByRow, &turnLeftRow, &turnRightRow);

				const char* frameName;
				float moveSpeed, imageSwapInterval, basePower;
				PyArg_ParseTuple(playerData, "sfff", &frameName, &moveSpeed, &imageSwapInterval ,&basePower);
				
				const char* uuid;
				PyArg_Parse(uuidData, "s", &uuid);
				Player* player = new Player(imagePath, glm::vec4(imageCol, imageRow, 0, 0), glm::vec4(1.0f), glm::vec3(scaleX, scaleY, scaleZ),
					glm::vec3(1,0,0), 0.0f, moveSpeed, imageSwapInterval, basePower, standByRow, turnLeftRow, turnRightRow);

				Player::addPlayerInstance(frameName, player);
#ifndef _DEBUG
				//Py_INCREF(retValue);
#else
				std::cout << "-------player entity item-------" << std::endl;
				std::cout << "entityName:" << frameName << " speed:" << moveSpeed << " swapInterval:" << imageSwapInterval << " basePower:" << basePower << std::endl;
				std::cout << "path:" << imagePath << " col:"<< imageCol << " row:"<< imageRow
					<< " standbyRow:"<< standByRow << " tLeftRow:"<< turnLeftRow <<" tRightRow:"<< turnRightRow << std::endl;
				
				std::cout  <<"scale:" << scaleX << " " << scaleY << " " << scaleZ<< " uuid:"<< uuid << std::endl;
				std::cout << "----------------------------\n" << std::endl;
				//Py_IncRef(retValue);
#endif

			}
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

