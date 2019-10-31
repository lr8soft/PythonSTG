#include "ItemHelper.h"
#include "../XCRender/RenderManager.h"
void ItemHelper::GenerateItemGroup(const glm::vec2 & generateCoord, int density, Item::ItemType itemType, bool exp)
{
	for (int i = 0; i < density; i++) {
		glm::vec2 coord = generateCoord;
		if (exp) {
			float c = 0.008f* density;
			if (rand() % 2==0) {
				
				if (rand() % 2 == 0) {
					coord.x += c * rand() / (RAND_MAX + 1.0);
					coord.y += c * rand() / (RAND_MAX + 1.0);
				}
				else {
					coord.x += c * rand() / (RAND_MAX + 1.0);
					coord.y -= c * rand() / (RAND_MAX + 1.0);
				}
			}
			else {
				if (rand() % 2 == 0) {
					coord.x -= c * rand() / (RAND_MAX + 1.0);
					coord.y += c * rand() / (RAND_MAX + 1.0);
				}
				else {
					coord.x -= c * rand() / (RAND_MAX + 1.0);
					coord.y -= c * rand() / (RAND_MAX + 1.0);
				}
			}
		}
		Item* item = new Item(glm::vec3(coord, 0.0f), itemType, 0.2f, (float)(rand() % 360), exp);
		RenderManager::getInstance()->AddRenderObject(ItemUniformUuid, item);
	}
}

std::vector<DropItem>* ItemHelper::getItemDropFromObject(PyObject * object)
{
	std::vector<DropItem>* dropItemVector = nullptr;

	auto dropInfo = PyObject_CallMethod(object, "_cpp_getDropItemSize", NULL);//_cpp_getDropItemSize;

	int dropItemSize = 0;
	PyArg_Parse(dropInfo, "i", &dropItemSize);
	if (dropItemSize > 0) {
		dropItemVector = new std::vector<DropItem>;
		for (int i = 0; i < dropItemSize; i++) {
			auto dropItem = PyObject_CallMethod(object, "_cpp_getDropItem", NULL);

			DropItem item;
			PyArg_ParseTuple(dropItem, "ii", &item.type, &item.count);
			dropItemVector->push_back(item);
		}
	}
	return dropItemVector;
}
