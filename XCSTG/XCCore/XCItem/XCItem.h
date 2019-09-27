#pragma once
#ifndef _XCItem_
#define _XCItem_
#include "../XCRender/IRenderHelper.h"
#include "../../util/GameTimer.h"
#include <glm/glm.hpp>
#include <string>
class XCItem {
protected:
	std::string itemUuid;
	bool itemWorkFinish = false;
	XCGameTimer itemTimer;

	IRenderHelper* renderHelper;
	glm::vec4 divideInfo;
	glm::vec4 coverColor;
	glm::vec3 scaleSize;
	glm::vec3 rotateWork;
	float rotateAngle = 0.0f;

	float NowPosition[3] = {0.0f, 0.0f, 0.0f};
public:
	XCItem(std::string uuid, IRenderHelper* image, glm::vec4 divideInfo, glm::vec4 coverColor ,glm::vec3 scaleSize, 
		glm::vec3 rotateWork ,float rotateAngle);

	virtual void ItemInit();
	virtual void ItemRender();
	virtual void ItemRelease();

	bool getIsFinish();
	float* getPosition();
	void setPosition(float x, float y, float z);
	std::string getUuid();
};
#endif