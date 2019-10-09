#include "CoverInterface.h"
#include "../XCRender/IRenderHelper.h"
#include "../../util/ImageLoader.h"
#include "../../util/ShaderReader.h"
#include "../../XCFrameInfo.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
std::string CoverInterface::imagePath;
CoverInterface* CoverInterface::pInterface = nullptr;
CoverInterface::CoverInterface() {
}

CoverInterface * CoverInterface::getInstance(std::string path)
{
	if (pInterface == nullptr) {
		imagePath = path;
		pInterface = new CoverInterface;
	}
	return pInterface;
}

void CoverInterface::UserInterfaceInit()
{
	if (!isInit) {
		ShaderReader fxreader;
		fxreader.loadFromFile("assets/Shader/image/image.bg.vert", GL_VERTEX_SHADER);
		fxreader.loadFromFile("assets/Shader/image/image.bg.frag", GL_FRAGMENT_SHADER);
		fxreader.linkAllShader();
		program = fxreader.getProgramHandle();

		ImageLoader image;
		image.loadTextureFromFile(imagePath.c_str());
		tbo = image.getTextureBufferObjectHandle();

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, IRenderHelper::GetSpecificTexture(1,1,1,1), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		isInit = true;
	}
}

void CoverInterface::UserInterfaceRender()
{
	if (isInit) {
		glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glUseProgram(program);
		glBindVertexArray(vao);

		glBindTexture(GL_TEXTURE_2D, tbo);

		auto limited_loc = glGetUniformLocation(program, "screen_info");
		auto mvp_loc = glGetUniformLocation(program, "mvp_mat");

		glm::mat4 mvp_mat;
		mvp_mat = glm::translate(mvp_mat, glm::vec3(0.0f, 0.0f, 0.0f));
		mvp_mat = glm::scale(mvp_mat, glm::vec3(1.0f));


		glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, glm::value_ptr(mvp_mat));
		glUniform2f(limited_loc, XCFrameInfo::ScreenWidth, XCFrameInfo::ScreenHeight);

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLushort), GL_UNSIGNED_SHORT, NULL);

		
		glUseProgram(0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
	}
}

void CoverInterface::UserInterfaceRelease()
{
	if (isInit) {
		glDeleteBuffers(1, &ebo);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		isInit = false;
	}
}
