#include "../../../util/ImageLoader.h"
#include "../../../util/ShaderReader.h"
#include "../../XCRender/IRenderHelper.h"
#include "../../../XCFrameInfo.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "XCParticle.h"
#include <GL3/gl3w.h>
using namespace xc_ogl;
GLuint XCParticle::tbo;
GLuint XCParticle::program;
bool XCParticle::have_tbo_init = false;
bool XCParticle::have_program_init = false;
void XCParticle::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader SELoader;
		SELoader.loadFromFile("assets/Shader/particle/particle.vert", GL_VERTEX_SHADER);
		SELoader.loadFromFile("assets/Shader/particle/particle.frag", GL_FRAGMENT_SHADER);
		SELoader.linkAllShader();
		program = SELoader.getProgramHandle();
		have_program_init = true;
	}
}

void XCParticle::TextureInit()
{
	if (!have_tbo_init) {
		ImageLoader imgLoader;
		imgLoader.loadTextureFromFile("assets/Item/particle.png");
		tbo = imgLoader.getTextureBufferObjectHandle();
		have_tbo_init = true;
	}

}

void XCParticle::BufferInit()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), IRenderHelper::GetPointSpriteVertex(15.0f), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

}


void XCParticle::particleInit()
{
	ShaderInit();
	TextureInit();
	BufferInit();
}

XCParticle::XCParticle(float lifeTime)
{
	particlelifeTime = lifeTime;
}

void XCParticle::particleRender(glm::vec3 position, float scaleSize, glm::vec4 color)
{	
	if (particlelifeTime >= timer.getAccumlateTime()) {
		timer.Tick();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glUseProgram(program);
		glEnable(GL_PROGRAM_POINT_SIZE);
		glBindVertexArray(vao);

		glBindTexture(GL_TEXTURE_2D, tbo);

		auto view_mat_loc = glGetUniformLocation(program, "view_mat");
		auto color_loc = glGetUniformLocation(program, "particle_color");
		auto size_loc = glGetUniformLocation(program, "particle_size");

		glm::mat4 view_mat;
		view_mat = glm::translate(view_mat, position);
		glUniformMatrix4fv(view_mat_loc, 1, GL_FALSE, glm::value_ptr(view_mat));

		glUniform4fv(color_loc, 1, glm::value_ptr(color));
	
		glUniform1f(size_loc, scaleSize);

		glDrawArrays(GL_POINTS, 0, 1);

		glDisable(GL_PROGRAM_POINT_SIZE);
		glDisable(GL_BLEND);
		glUseProgram(0);		
		glBindVertexArray(0);

	}
	else {
		isFinish = true;
	}
}


void XCParticle::particleRelease()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void XCParticle::particleReset()
{
	timer.Clear();
	isFinish = false;
}

bool XCParticle::getIsFinish()
{
	return isFinish;
}


