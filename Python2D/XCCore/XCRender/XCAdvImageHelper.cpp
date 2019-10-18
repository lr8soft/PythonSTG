#include "XCAdvImageHelper.h"

#include "../../XCFrameInfo.h"
#include "..\..\util\ImageLoader.h"
#include "..\..\util\ShaderReader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
GLuint XCAdvImageHelper::ProgramHandle = -1;
bool XCAdvImageHelper::haveProgramInit = false;

XCAdvImageHelper::XCAdvImageHelper(std::string path)
{
	imagePath = path;
	if (!haveProgramInit) {
		ShaderReader fxreader;
		fxreader.loadFromFile("assets/Shader/image/image.fx.vert", GL_VERTEX_SHADER);
		fxreader.loadFromFile("assets/Shader/image/image.fx.frag", GL_FRAGMENT_SHADER);
		fxreader.linkAllShader();
		ProgramHandle = fxreader.getProgramHandle();
		haveProgramInit = true;
	}

	ImageLoader imgLoader;
	imgLoader.loadTextureFromFile(path.c_str());
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

void XCAdvImageHelper::setMvpMatrix(const glm::mat4& mat)
{
	mvp_matrix = mat;
}


void XCAdvImageHelper::Render(const glm::vec3& renderPos, const glm::vec4& coverColor, float rotateAngle, const glm::vec3& rorateWorkCoord, const glm::vec3& scaleSize, float *texturePos16xFloat)
{

	glUseProgram(ProgramHandle);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindTexture(GL_TEXTURE_2D, tbo);

	auto color_location =  glGetUniformLocation(ProgramHandle, "diffuse");
	glUniform4fv(color_location, 1, glm::value_ptr(coverColor));

	auto mvp_fx_location = glGetUniformLocation(ProgramHandle, "mvp_mat");
	glUniformMatrix4fv(mvp_fx_location, 1, GL_FALSE, glm::value_ptr(mvp_matrix));

	glBufferSubData(GL_ARRAY_BUFFER, 0, 16 * sizeof(float), texturePos16xFloat);

	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLushort), GL_UNSIGNED_SHORT, NULL);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

void XCAdvImageHelper::Release()
{
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

}



GLuint XCAdvImageHelper::getProgramHandle()
{
	return ProgramHandle;
}

int XCAdvImageHelper::getHeight()
{
	return height;
}

int XCAdvImageHelper::getWidth()
{
	return width;
}
