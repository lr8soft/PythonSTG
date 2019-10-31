#pragma once
#ifndef _ITEM_HELPER_H_
#define _ITEM_HELPER_H_
#include <glm/glm.hpp>
#include "Item.h"
class ItemHelper {
public:
	static void GenerateItemGroup(const glm::vec2& generateCoord, int density, Item::ItemType itemType, bool itemExplode);

};
#endif