#include "XCInterpreter.h"
#include "ImageParseHelper.h"
#include "../XCCore/Task/TaskManager.h"
#include "../XCCore/Stage/Stage.h"
#include "../XCCore/Player/Player.h"
#include <string>
#include <chrono>
#include <future>
using namespace std;
InitInfo *XCInterpreter::gameInitInfo = nullptr;
XCInterpreter::XCInterpreter()
{

	
}
InitInfo* XCInterpreter::InterpreterThread()
{
	InitInfo* info = new InitInfo;
	MultiThreadDefine
	PyObject* mainScript = pyLoader.importModule("script.XCCore");
	pyLoader.callObjectMethod(mainScript, "coreInitializer", NULL);

	PyObject* title = pyLoader.getAttrib(mainScript, "winTitle");
	info->winTitle = pyLoader.getSingleArg<const char*>(title);

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
				PyObject* playerData = PyObject_CallMethod(pObject, "_cpp_getPlayerData", NULL);
				PyObject* uuidData = PyObject_CallMethod(pObject, "_cpp_getUUID", NULL);

				ImageInfo imgInfo = ImageParseHelper::parseImageHelperFromObject(pObject);

				const char* frameName;
				float moveSpeed, basePower;
				PyArg_ParseTuple(playerData, "sff", &frameName, &moveSpeed ,&basePower);
				
				const char* uuid;
				PyArg_Parse(uuidData, "s", &uuid);
				Player* player = new Player(imgInfo.imagePath, glm::vec4(imgInfo.divideColumn, imgInfo.divideRow, 0, 0),
					glm::vec4(1.0f), glm::vec3(imgInfo.zoomX, imgInfo.zoomY, 1.0f),
					glm::vec3(1,0,0), 0.0f, moveSpeed, imgInfo.swapSpeed, basePower, imgInfo.specialRow1, imgInfo.specialRow2, imgInfo.specialRow3);

				Player::addPlayerInstance(frameName, player);

			}
		}
	}
}

InitInfo* XCInterpreter::getInitInfo()
{
	if (gameInitInfo == nullptr) {	
		std::cout << "[INFO] Now Interpreter start." << std::endl;
		std::future<InitInfo*> retFuture = std::async(&XCInterpreter::InterpreterThread, this);
		gameInitInfo = retFuture.get();
	}
	return gameInitInfo;
}
void XCInterpreter::loadTaskManagerInfo()
{
	MultiThreadDefine
	parseStageItem();
	parsePlayerEntity();
	MultiThreadDefineEnd
}
XCInterpreter::~XCInterpreter()
{
	if (gameInitInfo != nullptr) {
		delete gameInitInfo;
		gameInitInfo = nullptr;
	}
}

