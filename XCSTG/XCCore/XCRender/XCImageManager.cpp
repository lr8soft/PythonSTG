#include "XCImageManager.h"
#include "..\..\util\ImageLoader.h"
#include "..\..\util\ShaderReader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
GLuint XCImageManager::ProgramHandle = -1;
bool XCImageManager::haveProgramInit = false;
std::map<std::string, GLuint> XCImageManager::textureGroup;
GLfloat vertices[] = {
	 1.0f, 1.0f,
	 1.0f,-1.0f,
	-1.0f,-1.0f,
	-1.0f, 1.0f
};
GLushort indices[] = {
	0, 1, 2, 2, 3, 0
};
XCImageManager::XCImageManager(std::string path)
{
	if (!haveProgramInit) {
		ShaderReader sreader;
		sreader.loadFromFile("XCCore/Shader/image/image.vert", GL_VERTEX_SHADER);
		sreader.loadFromFile("XCCore/Shader/image/image.frag", GL_FRAGMENT_SHADER);
		sreader.linkAllShader();
		ProgramHandle = sreader.getProgramHandle();
		haveProgramInit = true;
	}
	auto iter = textureGroup.find(path);
	if (iter ==textureGroup.end()) {
		ImageLoader imgLoader;
		imgLoader.loadTextureFromFile(path.c_str());
		tbo = imgLoader.getTextureBufferObjectHandle();
	}
	else {
		tbo = iter->second;
	}
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
}

void XCImageManager::ImageRender(glm::vec3 renderPos, glm::vec4 coverColor, glm::vec3 scaleSize)
{
	glUseProgram(ProgramHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, tbo);

	glm::mat4 mvp_mat;
	mvp_mat = glm::translate(mvp_mat, renderPos);
	mvp_mat = glm::scale(mvp_mat, scaleSize);
	auto mvp_location = glGetUniformLocation(ProgramHandle, "mvp_mat");
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp_mat));
	glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLushort), GL_UNSIGNED_SHORT, NULL);
	glBindVertexArray(0);
	glUseProgram(0);
}

void XCImageManager::ImageRelease()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}
