#pragma once
#ifndef _XCPARTICLE_H_
#define _XCPARTICLE_H_
#include "../../../util/GameTimer.h"
#include <gl/glcorearb.h>
#include <glm/glm.hpp>
class XCParticle {
	protected:
		bool isFinish = false;
		float particlelifeTime;
		GLuint vao, vbo;
		XCGameTimer timer;
		static bool have_tbo_init, have_program_init;
		static GLuint tbo, program;
		void ShaderInit();
		void TextureInit();
		void BufferInit();
	public:
		XCParticle(float lifeTimeSecond);
	    void particleRender(glm::vec3 position, float particleSize = 10.0f,glm::vec4 color=glm::vec4(1.0f));
		void particleInit();
		void particleRelease();

		void particleReset();
		bool getIsFinish();
};
#endif