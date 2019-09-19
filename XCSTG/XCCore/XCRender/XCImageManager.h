#pragma once
#ifndef _XCIMAGE_MANAGER_H_
#define _XCIMAGE_MANAGER_H_
#include <GL/glcorearb.h>
#include <map>
#include <glm/glm.hpp>
class XCImageManager {
private:
	GLuint vao, vbo, ebo, tbo;
	static GLuint ProgramHandle;
	static bool haveProgramInit;
	static std::map<std::string,GLuint> textureGroup;
public:
	XCImageManager() = delete;
	XCImageManager(std::string path);
	void ImageRender(glm::vec3 renderPos,glm::vec4 coverColor, glm::vec3 scaleSize=glm::vec3(1.0f, 1.0f, 1.0f));
	void ImageRelease();
};

#endif