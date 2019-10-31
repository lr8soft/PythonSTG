#include "ItemHelper.h"
#include "../XCRender/RenderManager.h"
void ItemHelper::GenerateItemGroup(const glm::vec2 & generateCoord, int density, Item::ItemType itemType, bool exp)
{
	for (int i = 0; i < density; i++) {
		Item* item = new Item(glm::vec3(generateCoord, 0.0f), itemType, 0.1f, (float)(rand() % 360), exp);
		RenderManager::getInstance()->AddRenderObject(ItemUniformUuid, item);
	}
}
