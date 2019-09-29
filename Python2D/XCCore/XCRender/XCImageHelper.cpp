#include "XCImageHelper.h"
#include "..\..\util\ImageLoader.h"
#include "..\..\util\ShaderReader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
GLuint XCImageHelper::ProgramHandle = -1;
GLuint XCImageHelper::ProgramHandleFx = -1;
bool XCImageHelper::haveProgramInit = false;
GLfloat vertices[] = {
	 1.0f, 1.0f,
	 1.0f,-1.0f,
	-1.0f,-1.0f,
	-1.0f, 1.0f
};
GLushort indices[] = {
	0, 1, 2, 2, 3, 0
};
XCImageHelper::XCImageHelper(std::string path, bool isRenderFlexible)
{
	isFlexible = isRenderFlexible;
	imagePath = path;
	if (!haveProgramInit) {
		ShaderReader sreader;
		sreader.loadFromFile("assets/Shader/image/image.vert", GL_VERTEX_SHADER);
		sreader.loadFromFile("assets/Shader/image/image.frag", GL_FRAGMENT_SHADER);
		sreader.linkAllShader();
		ProgramHandle = sreader.getProgramHandle();

		ShaderReader fxreader;
		fxreader.loadFromFile("assets/Shader/image/image.fx.vert", GL_VERTEX_SHADER);
		fxreader.loadFromFile("assets/Shader/image/image.fx.frag", GL_FRAGMENT_SHADER);
		fxreader.linkAllShader();
		ProgramHandleFx = fxreader.getProgramHandle();
		haveProgramInit = true;
	}

	ImageLoader imgLoader;
	imgLoader.loadTextureFromFile(path.c_str());
	tbo = imgLoader.getTextureBufferObjectHandle();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	if (!isFlexible) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(0);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, nullptr, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}
}

void XCImageHelper::Render(glm::vec3 renderPos, glm::vec4 coverColor, float rotateAngle, glm::vec3 rorateWorkCoord,glm::vec3 scaleSize, float *texuturePos16xFloat)
{
	if (!isFlexible)
		glUseProgram(ProgramHandle);
	else
		glUseProgram(ProgramHandleFx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindTexture(GL_TEXTURE_2D, tbo);

	glm::mat4 mvp_mat;
	mvp_mat = glm::translate(mvp_mat, renderPos);
	mvp_mat = glm::scale(mvp_mat, scaleSize);
	mvp_mat = glm::rotate(mvp_mat, glm::degrees(rotateAngle), rorateWorkCoord);
	if (!isFlexible) {
		auto mvp_location = glGetUniformLocation(ProgramHandle, "mvp_mat");
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp_mat));

	}
	else {
		auto mvp_location = glGetUniformLocation(ProgramHandleFx, "mvp_mat");
		glBufferSubData(GL_ARRAY_BUFFER, 0, 16 * sizeof(float), texuturePos16xFloat);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp_mat));
	}
	glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLushort), GL_UNSIGNED_SHORT, NULL);
	
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

void XCImageHelper::Release()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
//	glDeleteTextures(1,  &tbo);

//	textureGroup.erase(imagePath);
}


