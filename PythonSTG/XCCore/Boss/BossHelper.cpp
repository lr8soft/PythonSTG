#include "BossHelper.h"
#include <vector>
#include "../Task/TaskHelper.h"
#include "../Item/ItemHelper.h"
Boss * BossHelper::parseBossFromObject(PyObject * pBossPyObject)
{
	Boss* pBoss = nullptr;
	if (pBossPyObject!=nullptr) {
		auto bossInfoObject = PyObject_CallMethod(pBossPyObject, "_cpp_getBossInfo", NULL);
		auto imageInfoObject = PyObject_CallMethod(pBossPyObject, "_cpp_getImageInfo", NULL);
		auto spellCardSizeObject = PyObject_CallMethod(pBossPyObject, "_cpp_getSpellCardSize", NULL);
		auto targetUuidObject = PyObject_CallMethod(pBossPyObject, "_cpp_getTargetUuidSize", NULL);

		const char* bossName, *uuid, *music; int waitFrame;
		PyArg_ParseTuple(bossInfoObject, "ssis", &bossName, &uuid, &waitFrame, &music);

		const char* imagePath; int divideCols, divideRows, standByRow, walkRow, attackRow; float scaleX, scaleY;
		PyArg_ParseTuple(imageInfoObject, "s(ii)(ff)iii", &imagePath, &divideCols, &divideRows, &scaleX, &scaleY, &standByRow, &walkRow, &attackRow);

		int targetUUIDSize = 0;
		PyArg_Parse(targetUuidObject, "i", &targetUUIDSize);
		std::vector<std::string> targetUuidGroup;
		for (int i = 0; i < targetUUIDSize; i++) {
			const char* tuuid;
			auto targetInfo = PyObject_CallMethod(pBossPyObject, "_cpp_getTargetUuidSingle", NULL);
			PyArg_Parse(targetInfo, "s", &tuuid);

			targetUuidGroup.push_back(tuuid);
		}

		pBoss = new Boss(uuid, targetUuidGroup, bossName, music, waitFrame,
			imagePath,glm::vec2(divideCols, divideRows), glm::vec2(scaleX, scaleY), standByRow, walkRow, attackRow);

		int spellCardSize = 0;
		PyArg_Parse(spellCardSizeObject, "i", &spellCardSize);
		for (int i = 0; i < spellCardSize; i++) {
			PyObject *pSpellCardObject, *spellCardObject = PyObject_CallMethod(pBossPyObject, "_cpp_getSpellCardSingle", NULL);
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
		auto spellCardInfoObject = PyObject_CallMethod(spellCardPyObject, "_cpp_getSpellCardInfo", NULL);
		auto taskSizeObject = PyObject_CallMethod(spellCardPyObject, "_cpp_getTaskSize", NULL);//_cpp_getBossMovePosition
		auto movementObject = PyObject_CallMethod(spellCardPyObject, "_cpp_getBossMovePosition", NULL);

		float moveX, moveY;
		PyArg_ParseTuple(movementObject, "ff", &moveX, &moveY);

		const char* spellCardName; int isSpellCard; float spellCardTime, spellCardHitPoint;
		PyArg_ParseTuple(spellCardInfoObject, "siff", &spellCardName, &isSpellCard, &spellCardTime, &spellCardHitPoint);

		spellCard = new SpellCard(parentUuid, spellCardName, isSpellCard, spellCardTime, spellCardHitPoint);
		spellCard->setMovementPosition(moveX, moveY);

		int taskSize;
		PyArg_Parse(taskSizeObject, "i", &taskSize);
		for (int i = 0; i < taskSize; i++) {
			PyObject* taskPyObject, *taskSRCObject = PyObject_CallMethod(spellCardPyObject, "_cpp_getTaskItem", NULL);
			PyArg_Parse(taskSRCObject, "O", &taskPyObject);

			Task* task = TaskHelper::parseTaskFromObject(taskPyObject);
			if (task != nullptr) {
				spellCard->AddSpellCardTask(task);
			}
		}

		std::vector<DropItem>* itemVector = ItemHelper::getItemDropFromObject(spellCardPyObject);
		if (itemVector != nullptr) {
			spellCard->setDropItem(itemVector);
		}

	}
	return spellCard;
}
