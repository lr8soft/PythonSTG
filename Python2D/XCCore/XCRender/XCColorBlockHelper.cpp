#include "XCColorBlockHelper.h"
#include "..\..\util\ShaderReader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../XCFrameInfo.h"
using namespace xc_ogl;
GLuint XCColorBlockHelper::ProgramHandle = -1, XCColorBlockHelper::ProgramHandleFx = -1;
bool XCColorBlockHelper::haveProgramInit = false;
namespace data {
GLfloat vertices[] = {
	 1.0f, 1.0f,
	 1.0f,-1.0f,
	-1.0f,-1.0f,
	-1.0f, 1.0f
};
GLushort indices[] = {
	0, 1, 2, 2, 3, 0
};
}

XCColorBlockHelper::XCColorBlockHelper(bool fx)
{
	isFlexible = fx;
	if (!haveProgramInit) {
		ShaderReader sreader;
		sreader.loadFromFile("assets/Shader/default/default.vert", GL_VERTEX_SHADER);
		sreader.loadFromFile("assets/Shader/default/default.frag", GL_FRAGMENT_SHADER);
		sreader.linkAllShader();
		ProgramHandle = sreader.getProgramHandle();

		ShaderReader fxreader;
		fxreader.loadFromFile("assets/Shader/default/default.fx.vert", GL_VERTEX_SHADER);
		fxreader.loadFromFile("assets/Shader/default/default.fx.frag", GL_FRAGMENT_SHADER);
		fxreader.linkAllShader();
		ProgramHandleFx = fxreader.getProgramHandle();
		haveProgramInit = true;
	}
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data::indices), data::indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	if (!isFlexible) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(data::vertices), data::vertices, GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, sizeof(data::vertices), nullptr, GL_DYNAMIC_DRAW);
	}
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
}

void XCColorBlockHelper::Render(glm::vec3 renderPos, glm::vec4 coverColor, float rotateAngle, glm::vec3 rotateWork, glm::vec3 scaleSize, float * dataPointer)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (!isFlexible) 
		glUseProgram(ProgramHandle);
	else
		glUseProgram(ProgramHandleFx);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	if (isFlexible) {
		glBufferSubData(GL_ARRAY_BUFFER, 0,  sizeof(data::vertices), IRenderHelper::GetSquareVertices(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop));
	}
	glm::mat4 mvp_mat;
	if (!isFlexible) {
		mvp_mat = glm::translate(mvp_mat, renderPos);
	}
	else {
		mvp_mat = glm::translate(mvp_mat, renderPos * glm::vec3(XCFrameInfo::FrameRight, XCFrameInfo::FrameTop, 1.0f));
	}
	mvp_mat = glm::scale(mvp_mat, scaleSize);
	mvp_mat = glm::rotate(mvp_mat, glm::degrees(rotateAngle), rotateWork);
	
	auto mvp_location = glGetUniformLocation(ProgramHandle, "mvp_mat");
	if (isFlexible) {
		auto color_location = glGetUniformLocation(ProgramHandleFx, "diffuse_color");
		glUniform4fv(color_location, 1, glm::value_ptr(coverColor));
	}
	else{
		auto color_location = glGetUniformLocation(ProgramHandle, "font_color");
		glUniform4fv(color_location, 1, glm::value_ptr(coverColor));
	}
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp_mat));
	
	glDrawElements(GL_TRIANGLES, sizeof(data::indices) / sizeof(GLushort), GL_UNSIGNED_SHORT, NULL);

	glDisable(GL_BLEND);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

void XCColorBlockHelper::Release()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}
