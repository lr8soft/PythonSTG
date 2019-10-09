#pragma once
#ifndef _COVER_INTERFACE_H_
#define _COVER_INTERFACE_H_
#include "IUserInterface.h"
#include <GL/glcorearb.h>
class CoverInterface : public IUserInterface{
private:
	static CoverInterface* pInterface;

	GLushort indices[6] = { 0, 1, 2, 2, 3, 0 };
	GLfloat vertices[8] = {1.0f, 1.0f, 1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 1.0f};
	GLuint vao, vbo, ebo, tbo, program;

	CoverInterface();
public:
	static CoverInterface* getInstance();

	virtual void UserInterfaceInit();
	virtual void UserInterfaceRender();
	virtual void UserInterfaceRelease();
};
#endif