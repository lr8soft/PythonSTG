#pragma once
#ifndef _XCColorBlockManager_H_
#define _XCColorBlockManager_H_
#include "IRenderHelper.h"
#include <GL/glcorearb.h>

class XCColorBlockHelper:public IRenderHelper {
private:
	static GLuint ProgramHandle;
	static bool haveProgramInit;
	GLuint vao, vbo, ebo;
public:
	XCColorBlockHelper();
	virtual void Render(glm::vec3 renderPos, glm::vec4 coverColor, float rotateAngle = 0.0f, glm::vec3 rotateWork = glm::vec3(0, 0, 0),
		glm::vec3 scaleSize = glm::vec3(1.0f, 1.0f, 1.0f), float *dataPointer = nullptr);
	virtual void Release();
};
#endif