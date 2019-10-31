#pragma once
#ifndef _ITEM_HELPER_H_
#define _ITEM_HELPER_H_
#include <vector>
#include <Python.h>
#include <glm/glm.hpp>
#include "Item.h"
struct DropItem {
	int type;
	int count;
};
class ItemHelper {
public:
	static void GenerateItemGroup(const glm::vec2& generateCoord, int density, Item::ItemType itemType, bool itemExplode);
	static std::vector<DropItem>* getItemDropFromObject(PyObject* object);
};
#endif