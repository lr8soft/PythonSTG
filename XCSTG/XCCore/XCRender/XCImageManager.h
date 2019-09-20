#pragma once
#ifndef _XCIMAGE_MANAGER_H_
#define _XCIMAGE_MANAGER_H_
#include <GL/glcorearb.h>
#include <map>
#include <glm/glm.hpp>
class XCImageManager {
private:
	bool isFlexible;
	GLuint vao, vbo, ebo, tbo;
	std::string imagePath;
	static GLuint ProgramHandle, ProgramHandleFx;
	static bool haveProgramInit;
	static std::map<std::string,GLuint> textureGroup;
public:
	XCImageManager() = delete;
	/*isRenderFlexible=true下，渲染时请给texuturePos16xFloat赋值*/
	XCImageManager(std::string path, bool isRenderFlexible = false);

	/*在flexible状态下，texuturePos16xFloat指针应该为GetSpecificTexture或者GetSpecificTexWithWidthAndHeight的返回值*/
	void ImageRender(glm::vec3 renderPos,glm::vec4 coverColor, 
		glm::vec3 scaleSize=glm::vec3(1.0f, 1.0f, 1.0f), float *texuturePos16xFloat=nullptr);
	void ImageRelease();

	/*共column列，row行；取第x列 第y行（以该子纹理右上角坐标为准）*/
	static float* GetSpecificTexture(int column, int row, int x, int y);
	/*共column列，row行；取第x列 第y行（以该子纹理右上角坐标为准）*/
	static float* GetSpecificTexWithRate(float width_rate, float height_rate, int column, int row, int x, int y);
	static float* GetPointSpriteVertex(float size);
};

#endif