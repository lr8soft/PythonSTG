#include "XCFlexibleImageHelper.h"

#include "../../XCFrameInfo.h"
#include "..\..\util\ImageLoader.h"
#include "..\..\util\ShaderReader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace xc_ogl;
GLuint XCFlexibleImageHelper::ProgramHandle = -1;
bool XCFlexibleImageHelper::haveProgramInit = false;
XCFlexibleImageHelper::XCFlexibleImageHelper(std::string shaderPath, std::string imagePath)
{
	imagePath = imagePath;
	if (!haveProgramInit) {
		ShaderReader fxreader;
		fxreader.loadFromFile((shaderPath + ".vert").c_str(), GL_VERTEX_SHADER);
		fxreader.loadFromFile((shaderPath + ".frag").c_str(), GL_FRAGMENT_SHADER);
		fxreader.linkAllShader();
		ProgramHandle = fxreader.getProgramHandle();
		haveProgramInit = true;
	}

	ImageLoader imgLoader;
	imgLoader.loadTextureFromFile(imagePath.c_str());
	tbo = imgLoader.getTextureBufferObjectHandle();
	width = imgLoader.getTextureWidth();
	height = imgLoader.getTextureHeight();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void XCFlexibleImageHelper::Render(const glm::vec3 & a, const glm::vec4 & b, float c, const glm::vec3 & d, const glm::vec3 & e, float * f)
{
	throw("Invalid method!");
}

void XCFlexibleImageHelper::Render(float * pDataInfo)
{
	glUseProgram(ProgramHandle);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindTexture(GL_TEXTURE_2D, tbo);

	glBufferSubData(GL_ARRAY_BUFFER, 0, 16 * sizeof(float), pDataInfo);
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLushort), GL_UNSIGNED_SHORT, NULL);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

void XCFlexibleImageHelper::Release()
{
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void XCFlexibleImageHelper::setShaderUniform1f(std::string varName, float value)
{
	glUseProgram(ProgramHandle);
	auto location = glGetUniformLocation(ProgramHandle, varName.c_str());
	glUniform1f(location, value);

	glUseProgram(0);
}

void XCFlexibleImageHelper::setShaderUniform2fv(std::string varName, float * pData)
{
	glUseProgram(ProgramHandle);
	auto location = glGetUniformLocation(ProgramHandle, varName.c_str());
	glUniform2fv(location, 1, pData);
	glUseProgram(0);
}

void XCFlexibleImageHelper::setShaderUniform4fv(std::string varName, float * pData)
{
	glUseProgram(ProgramHandle);
	auto location = glGetUniformLocation(ProgramHandle, varName.c_str());
	glUniform4fv(location, 1, pData);
	glUseProgram(0);
}

void XCFlexibleImageHelper::setShaderUniformMatrix(std::string varName, float * pData)
{
	glUseProgram(ProgramHandle);
	auto location = glGetUniformLocation(ProgramHandle, varName.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, pData);
	glUseProgram(0);
}

int XCFlexibleImageHelper::getHeight()
{
	return height;
}

int XCFlexibleImageHelper::getWidth()
{
	return width;
}
