#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_
#include <glm/glm.hpp>
#include "../XCRender/RenderObject.h"
#include "../XCRender/IRenderHelper.h"
#include "../../util/GameTimer.h"
#define ItemUniformUuid "ItemUniformUUID"
class Item :public RenderObject {
public:
	enum ItemType {
		PointType = 0, PowerType, FullPowerType, LifeType, BombType
	};
protected:
	XCGameTimer timer;

	ItemType currentType;
	glm::vec2 NowPosition;
	glm::vec4 divideInfo;
	float velocity;

	IRenderHelper* itemImage;
public:
	Item(const glm::vec2& generateCoord, ItemType itemType, float fallVelocity);
	virtual void Init() override;
	virtual void Render() override;
	virtual void Release() override;

	//void checkCollideWithPlayer();
};

#endif