#pragma once
#ifndef _XCADVIMAGE_HELPER_H_
#define _XCADVIMAGE_HELPER_H_
#include <GL/glcorearb.h>
#include "IRenderHelper.h"
#include <iostream>
class XCAdvImageHelper :public IRenderHelper {
private:
	GLushort indices[6] = {0, 1, 2, 2, 3, 0};
	glm::mat4 mvp_matrix;
	GLuint vao, vbo, ebo, tbo;
	std::string imagePath;
	static GLuint ProgramHandle;
	static bool haveProgramInit;

	int width = 0, height = 0;
public:
	XCAdvImageHelper() = delete;
	XCAdvImageHelper(std::string path);

	void setMvpMatrix(const glm::mat4& mvp_mat);
	/*…Ë÷√mvpæÿ’Û«ÎsetMvpMatrix*/
	virtual void Render(const glm::vec3& placeholderVec3, const glm::vec4& coverColor, float placeholder = 0.0f, const glm::vec3& PlaceholderVec3_2 = glm::vec3(0, 0, 0),
		const glm::vec3& placeholderVec3_3 = glm::vec3(1.0f, 1.0f, 1.0f), float *texuturePos16xFloat = nullptr) override;
	virtual void Release() override;

	static GLuint getProgramHandle();

	int getHeight();
	int getWidth();
};
#endif