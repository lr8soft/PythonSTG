#pragma once
#ifndef _XCIMAGE_MANAGER_H_
#define _XCIMAGE_MANAGER_H_
#include <GL/glcorearb.h>
#include <map>
#include "IRenderHelper.h"
class XCImageHelper:public IRenderHelper {
private:
	bool isFlexible;
	GLuint vao, vbo, ebo, tbo;
	std::string imagePath;
	static GLuint ProgramHandle, ProgramHandleFx;
	static bool haveProgramInit;
	static std::map<std::string,GLuint> textureGroup;
public:
	XCImageHelper() = delete;
	/*isRenderFlexible=true下，渲染时请给texuturePos16xFloat赋值*/
	XCImageHelper(std::string path, bool isRenderFlexible = false);

	/*在flexible状态下，texuturePos16xFloat指针应该为GetSpecificTexture或者GetSpecificTexWithWidthAndHeight的返回值*/
	virtual void Render(glm::vec3 renderPos,glm::vec4 coverColor, 
		glm::vec3 scaleSize=glm::vec3(1.0f, 1.0f, 1.0f), float *texuturePos16xFloat=nullptr) override;
	virtual void Release() override;

	/*共column列，row行；取第x列 第y行（以该子纹理右上角坐标为准）*/
	static float* GetSpecificTexture(int column, int row, int x, int y);
	/*共column列，row行；取第x列 第y行（以该子纹理右上角坐标为准）*/
	static float* GetSpecificTexWithRate(float width_rate, float height_rate, int column, int row, int x, int y);
	static float* GetPointSpriteVertex(float size);
};

#endif