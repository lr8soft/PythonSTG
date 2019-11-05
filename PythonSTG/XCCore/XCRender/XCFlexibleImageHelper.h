#pragma once
#pragma once
#ifndef _XCFX_HELPER_H_
#define _XCFX_HELPER_H_
#include <GL/glcorearb.h>
#include "IRenderHelper.h"
#include <iostream>
class XCFlexibleImageHelper :public IRenderHelper {
private:
	GLushort indices[6] = { 0, 1, 2, 2, 3, 0 };
	glm::mat4 mvp_matrix;
	GLuint vao, vbo, ebo, tbo;
	std::string imagePath;
	static GLuint ProgramHandle;
	static bool haveProgramInit;

	int width = 0, height = 0;
public:
	XCFlexibleImageHelper(std::string shaderPath, std::string imagePath);
	/*无用方法*/
	virtual void Render(const glm::vec3& a, const glm::vec4& b, float c = 0.0f, const glm::vec3& d = glm::vec3(0, 0, 0),
		const glm::vec3& e = glm::vec3(1.0f, 1.0f, 1.0f), float *f = nullptr) override;
	virtual void Render(float* pDataInfo);
	virtual void Release() override;

	void setShaderUniform1f(std::string varName, float value);
	void setShaderUniform4fv(std::string varName, float* pData);
	void setShaderUniformMatrix(std::string varName, float *pData);

	int getHeight();
	int getWidth();
};
#endif