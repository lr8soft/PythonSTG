#pragma once
#ifndef _IRENDER_MANAGER_H_
#define _IRENDER_MANAGER_H_
#include <glm/glm.hpp>
#include <iostream>
class IRenderHelper {
public:
	virtual void Render(const glm::vec3& renderPos, const glm::vec4& coverColor, float rotateAngleRadians = 0.0f, const glm::vec3& rotateWork = glm::vec3(0, 0, 0),
		const glm::vec3& scaleSize = glm::vec3(1.0f, 1.0f, 1.0f), float *dataPointer = nullptr) = 0;
	virtual void Release() = 0;


	/*共column列，row行；取第x列 第y行（以左下为坐标轴原点）*/
	static float* GetSpecificTexture(int column, int row, int ix, int iy, float xoffset = 0.0f, float yoffset = 0.0f);

	/*共column列，row行；取第x列 第y行（以左下为坐标轴原点）*/
	static float* GetSpecificTexturef(int column, int row, float xcoord, float ycoord, float xoffset = 0.0f, float yoffset = 0.0f);

	/*共column列，row行；取第x列 第y行（以左下为坐标轴原点）*/
	static float * GetSpecificTexWithRate(float width_rate, float height_rate, int column, int row, int ix, int iy, float xoffset = 0.0f, float yoffset = 0.0f);

	/*共column列，row行；取(xcoord, ycoord)处纹理数据（以左下为坐标轴原点）*/
	static float * GetSpecificTexWithRatef(float width_rate, float height_rate, int column, int row, float xcoord, float ycoord, float xoffset = 0.0f, float yoffset = 0.0f);

	static float *GetSquareVertices(float widthRate, float heightRate);

	static float * GetPointSpriteVertex(float size);

	static IRenderHelper* getRenderObjectByType(std::string type, std::string path, bool isFlexible);
};

#endif