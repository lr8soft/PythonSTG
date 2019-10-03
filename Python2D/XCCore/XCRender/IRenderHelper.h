#pragma once
#ifndef _IRENDER_MANAGER_H_
#define _IRENDER_MANAGER_H_
#include <glm/glm.hpp>
class IRenderHelper {
public:
	virtual void Render(glm::vec3 renderPos, glm::vec4 coverColor, float rotateAngle = 0.0f, glm::vec3 rotateWork = glm::vec3(0, 0, 0),
		glm::vec3 scaleSize = glm::vec3(1.0f, 1.0f, 1.0f), float *dataPointer = nullptr) = 0;
	virtual void Release() = 0;


	/*共column列，row行；取第x列 第y行（以该子纹理右上角坐标为准）*/
	static float* GetSpecificTexture(int column, int row, int ix, int iy)
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

	/*共column列，row行；取第x列 第y行（以该子纹理右上角坐标为准）*/
	static float * GetSpecificTexWithRate(float width_rate, float height_rate, int column, int row, int ix, int iy)
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
	static float *GetSquareVertices(float widthRate, float heightRate) {
		static float vertices[8] = {
			 widthRate, heightRate,
			 widthRate,-heightRate,
			-widthRate,-heightRate,
			-widthRate, heightRate
		};
		return vertices;

	}
	static float * GetPointSpriteVertex(float size)
	{
		static float returnArray[4];
		returnArray[0] = 0.0f;
		returnArray[1] = 0.0f;
		returnArray[2] = 0.0f;
		returnArray[3] = size;
		return returnArray;
	}
};
#endif