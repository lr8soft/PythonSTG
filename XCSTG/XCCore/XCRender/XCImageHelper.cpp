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
std::map<std::string, GLuint> XCImageHelper::textureGroup;
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
	if (!isFlexible) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, nullptr, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	glEnableVertexAttribArray(0);
}

void XCImageHelper::Render(glm::vec3 renderPos, glm::vec4 coverColor, float rotateAngle, glm::vec3 rorateWorkCoord,glm::vec3 scaleSize, float *texuturePos16xFloat)
{
	if (!isFlexible)
		glUseProgram(ProgramHandle);
	else
		glUseProgram(ProgramHandleFx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, tbo);

	glm::mat4 mvp_mat;
	mvp_mat = glm::translate(mvp_mat, renderPos);
	mvp_mat = glm::rotate(mvp_mat, glm::degrees(rotateAngle), rorateWorkCoord);
	mvp_mat = glm::scale(mvp_mat, scaleSize);
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


float* XCImageHelper::GetSpecificTexture(int column, int row, int ix, int iy)
{
	float x = ix; float y = iy;
	static float returnArray[16];
	returnArray[0] = 1.0f;
	returnArray[1] = 1.0f;
	returnArray[2] = x / column;
	returnArray[3] = y / row;

	returnArray[4] = 1.0f;
	returnArray[5] = -1.0f,
		returnArray[6] = x / column;
	returnArray[7] = (y - 1) / row;

	returnArray[8] = -1.0f;
	returnArray[9] = -1.0f,
		returnArray[10] = (x - 1) / column;
	returnArray[11] = (y - 1) / row;


	returnArray[12] = -1.0f;
	returnArray[13] = 1.0f,
		returnArray[14] = (x - 1) / column;
	returnArray[15] = y / row;
	return returnArray;
}
float * XCImageHelper::GetSpecificTexWithRate(float width_rate, float height_rate, int column, int row, int ix, int iy)
{
	float x = ix; float y = iy;
	static float returnArray[16];
	returnArray[0] = width_rate;
	returnArray[1] = height_rate;
	returnArray[2] = x / column;
	returnArray[3] = y / row;

	returnArray[4] = width_rate;
	returnArray[5] = -height_rate,
	returnArray[6] = x / column;
	returnArray[7] = (y - 1) / row;

	returnArray[8] = -width_rate;
	returnArray[9] = -height_rate,
	returnArray[10] = (x - 1) / column;
	returnArray[11] = (y - 1) / row;

	returnArray[12] = -width_rate;
	returnArray[13] = height_rate,
	returnArray[14] = (x - 1) / column;
	returnArray[15] = y / row;

	return returnArray;
}
float * XCImageHelper::GetPointSpriteVertex(float size)
{
	static float returnArray[4];
	returnArray[0] = 0.0f;
	returnArray[1] = 0.0f;
	returnArray[2] = 0.0f;
	returnArray[3] = size;
	return returnArray;
}