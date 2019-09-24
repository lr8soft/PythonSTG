#include "XCColorBlockHelper.h"
#include "..\..\util\ShaderReader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
GLuint XCColorBlockHelper::ProgramHandle = -1;
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

XCColorBlockHelper::XCColorBlockHelper()
{
	if (!haveProgramInit) {
		ShaderReader sreader;
		sreader.loadFromFile("assets/Shader/default/default.vert", GL_VERTEX_SHADER);
		sreader.loadFromFile("assets/Shader/default/default.frag", GL_FRAGMENT_SHADER);
		sreader.linkAllShader();
		ProgramHandle = sreader.getProgramHandle();
		haveProgramInit = true;
	}
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data::indices), data::indices, GL_STATIC_DRAW);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data::vertices), data::vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
}

void XCColorBlockHelper::Render(glm::vec3 renderPos, glm::vec4 coverColor, glm::vec3 scaleSize, float * dataPointer)
{
	glUseProgram(ProgramHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBindVertexArray(vao);
	glm::mat4 mvp_mat;
	mvp_mat = glm::translate(mvp_mat, renderPos);
	mvp_mat = glm::scale(mvp_mat, scaleSize);
	auto mvp_location = glGetUniformLocation(ProgramHandle, "mvp_mat");
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp_mat));
	glDrawElements(GL_TRIANGLES, sizeof(data::indices) / sizeof(GLushort), GL_UNSIGNED_SHORT, NULL);
	glBindVertexArray(0);
	glUseProgram(0);
}

void XCColorBlockHelper::Release()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}
