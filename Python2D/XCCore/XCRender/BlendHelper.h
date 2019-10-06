#pragma once
#ifndef _BLEND_HELPER_H_
#define _BLEND_HELPER_H_
#include <GL3/gl3w.h>

#define BlendNormalStart\
	glEnable(GL_BLEND);\

#define BlendOneMinusAlphaStart \
	glEnable(GL_BLEND); \
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);\

#define BlendOneMinusAlphaColorStart \
	glEnable(GL_BLEND); \
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);\
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);\

#define BlendAlphaOneStart \
	glEnable(GL_BLEND); \
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);\


#define BlendAlphaColorOneStart \
	glEnable(GL_BLEND); \
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);\
	glBlendFunc(GL_SRC_COLOR, GL_ONE);\

#define BlendEnd \
	glDisable(GL_BLEND); \

#endif