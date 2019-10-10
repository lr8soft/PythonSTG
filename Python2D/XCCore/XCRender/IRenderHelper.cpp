#include "IRenderHelper.h"
#include "XCImageHelper.h"
#include "XCColorBlockHelper.h"
float * IRenderHelper::GetSpecificTexture(int column, int row, int ix, int iy)
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
float * IRenderHelper::GetSpecificTexturef(int column, int row, float xcoord, float ycoord)
{
	float x = xcoord; float y = ycoord;
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
float * IRenderHelper::GetSpecificTexWithRate(float width_rate, float height_rate, int column, int row, int ix, int iy)
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
float * IRenderHelper::GetSpecificTexWithRatef(float width_rate, float height_rate, int column, int row, float xcoord, float ycoord)
{
	static float returnArray[16];
	returnArray[0] = width_rate;
	returnArray[1] = height_rate;
	returnArray[2] = xcoord / column;
	returnArray[3] = ycoord / row;

	returnArray[4] = width_rate;
	returnArray[5] = -height_rate,
		returnArray[6] = xcoord / column;
	returnArray[7] = (ycoord - 1) / row;

	returnArray[8] = -width_rate;
	returnArray[9] = -height_rate,
		returnArray[10] = (xcoord - 1) / column;
	returnArray[11] = (ycoord - 1) / row;

	returnArray[12] = -width_rate;
	returnArray[13] = height_rate,
		returnArray[14] = (xcoord - 1) / column;
	returnArray[15] = ycoord / row;

	return returnArray;
}
float * IRenderHelper::GetSquareVertices(float widthRate, float heightRate)
{
	static float vertices[8] = {
		 widthRate, heightRate,
		 widthRate,-heightRate,
		-widthRate,-heightRate,
		-widthRate, heightRate
	};
	return vertices;

}
float * IRenderHelper::GetPointSpriteVertex(float size)
{
	static float returnArray[4];
	returnArray[0] = 0.0f;
	returnArray[1] = 0.0f;
	returnArray[2] = 0.0f;
	returnArray[3] = size;
	return returnArray;
}
IRenderHelper * IRenderHelper::getRenderObjectByType(std::string type, std::string path, bool isFlexible)
{
	IRenderHelper *image = nullptr;
	if ("image" == type) {
		image = new XCImageHelper(path, isFlexible);
	}
	else if ("colorblock" == type) {
		image = new XCColorBlockHelper(isFlexible);
	}

	return image;
}
