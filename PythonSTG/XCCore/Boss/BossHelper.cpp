#include "BossHelper.h"
#include <vector>
Boss * BossHelper::parseBossFromObject(PyObject * pBossPyObject)
{
	Boss* pBoss = nullptr;
	if (pBossPyObject!=nullptr) {
		auto bossInfoObject = PyObject_CallMethod(pBossPyObject, "_cpp_getBossInfo", NULL);
		auto imageInfoObject = PyObject_CallMethod(pBossPyObject, "_cpp_getImageInfo", NULL);
		auto spellCardSizeObject = PyObject_CallMethod(pBossPyObject, "_cpp_getSpellCardSize", NULL);
		auto targetUuidObject = PyObject_CallMethod(pBossPyObject, "_cpp_getTargetUuidSize", NULL);

		const char* bossName, *uuid; int waitFrame;
		PyArg_ParseTuple(bossInfoObject, "ssi", &bossName, &uuid, &waitFrame);

		const char* imagePath; int divideCols, divideRows, standByRow, walkRow, attackRow;
		PyArg_ParseTuple(imageInfoObject, "siiiii", &imagePath, &divideCols, &divideRows, &standByRow, &walkRow, &attackRow);

		int targetUUIDSize = 0;
		PyArg_Parse(targetUuidObject, "i", &targetUUIDSize);
		std::vector<std::string> targetUuidGroup;
		for (int i = 0; i < targetUUIDSize; i++) {
			const char* tuuid;
			auto targetInfo = PyObject_CallMethod(pBossPyObject, "_cpp_getTargetUuidSingle", NULL);
			PyArg_Parse(targetInfo, "s", &tuuid);
			targetUuidGroup.push_back(tuuid);
		}

		pBoss = new Boss(uuid, targetUuidGroup, bossName, waitFrame,imagePath,glm::vec2(divideCols, divideRows),standByRow, walkRow, attackRow);

		int spellCardSize = 0;
		PyArg_Parse(spellCardSizeObject, "i", &spellCardSize);
		for (int i = 0; i < spellCardSize; i++) {
			PyObject *pSpellCardObject, *spellCardObject = PyObject_CallMethod(pBossPyObject, "_cpp_getSpellCardItem", NULL);
			PyArg_Parse(spellCardObject, "O", &pSpellCardObject);
			SpellCard *spellCard = parseSpellCardFromObject(uuid, pSpellCardObject);
			if (spellCard != nullptr) {
				pBoss->AddSpellCard(spellCard);
			}
		}
	}

	return pBoss;
}

SpellCard * BossHelper::parseSpellCardFromObject(std::string parentUuid, PyObject * spellCardPyObject)
{
	SpellCard* spellCard = nullptr;
	if (spellCardPyObject!=nullptr) {

	}
	return spellCard;
}
