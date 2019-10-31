#include "Boss.h"
#include "../XCRender/XCImageHelper.h"
#include "../Task/TaskManager.h"
#include "../Task/TaskDispatcher.h"
#include "../XCRender/RenderManager.h"
#include "../UserInterface/BossInfoInterface.h"
#include "../Item/ItemHelper.h"
Boss::Boss(std::string uid, std::vector<std::string>& targetUUID,std::string bName, std::string musicPath,int wFrame,
	std::string imgPath, glm::vec2 dInfo, glm::vec2 sInfo, int sbRow, int wRow, int aRow):Task(uid,targetUUID, 1, 0, wFrame)
{
	bossName = bName;
	currentUuid = uid;

	imagePath = imgPath;
	divideInfo = dInfo;
	scaleInfo = sInfo;
	standByRow = sbRow;
	walkRow = wRow;
	attackRow = aRow;

	if (!musicPath.empty()) {
		haveBossMusic = true;
		bossMusicPath = musicPath;
	}
}

void Boss::AddSpellCard(SpellCard * spellcard)
{
	spellCardGroup.push_back(spellcard);
}

void Boss::TaskInit()
{
	if (!taskIsInit) {
		XCImageHelper* image = new XCImageHelper(imagePath, true);
		bossRenderObject = new BossObject(image, divideInfo, scaleInfo, standByRow, walkRow, attackRow);

		for (auto spellcard = spellCardGroup.begin(); spellcard != spellCardGroup.end(); spellcard++) {
			(*spellcard)->SpellCardInit();
			(*spellcard)->setBossObject(bossRenderObject);
		}

		if (haveBossMusic) {
			bossMusic = AudioHelper::loadWavByAlut(bossMusicPath);
			stageMusic = TaskManager::getInstance()->getCurrentStageMusic();
		}

		taskIsInit = true;
	}

}

void Boss::TaskWork()
{
	if (taskIsInit) {
		if (targetUUID.empty()) {
			taskSubWork();
			taskWaitForTarget = false;
			if (haveBossMusic) {
				AudioHelper::stopByBuffer(stageMusic);
				AudioHelper::playFromBuffer(bossMusic);
			}
		}
		else {
			bool isAllTargetFinish = true;
			for (int i = 0; i < targetUUID.size(); i++) {
				bool isTargetFinish = TaskDispatcher::getTaskFinish(targetUUID[i]);
				if (!isTargetFinish) {
					isAllTargetFinish = false;
					taskWaitForTarget = true;
				}
			}
			if (isAllTargetFinish) {
				taskSubWork();
				taskWaitForTarget = false;
				if (haveBossMusic) {
					AudioHelper::stopByBuffer(stageMusic);
					AudioHelper::playFromBuffer(bossMusic);
				}
			}
		}
	}
}

void Boss::taskSubWork()
{
	if (taskWaitFrame > 0) {
		taskWaitFrame--;
		taskWait = true;
	}
	else {
		taskWait = false;
		if (!haveAddRenderObjectToQueue) {
			RenderManager::getInstance()->AddRenderObject(currentUuid, bossRenderObject, false);
			RenderManager::getInstance()->AddUserInterface(BossInfoInterfaceUuid, BossInfoInterface::getInstance());
			haveAddRenderObjectToQueue = true;
		}
		auto spellCardBegin = spellCardGroup.begin();
		auto spellCardEnd = spellCardGroup.end();
		if (spellCardBegin != spellCardEnd) {
			if (!(*spellCardBegin)->getIsFinish()) {
				if (isNewSpellCard) {
					
					BossInfoInterface::getInstance()->setBossName(bossName);
					BossInfoInterface::getInstance()->setSpellCardCount(spellCardGroup.size());
					BossInfoInterface::getInstance()->setSpellCardName((*spellCardBegin)->getSpellCardName());

					bossRenderObject->setBossHitPoint((*spellCardBegin)->getSpellCardHitPoint());
					bossRenderObject->setBossSpellCardCount(spellCardGroup.size());
					bossRenderObject->setBossSpellCardTime((*spellCardBegin)->getSpellCardTime());
					bossRenderObject->setMovement((*spellCardBegin)->getMovement());
					bossRenderObject->setSpellCardFinish(false);
					isNewSpellCard = false;
				}
				bool bossFinishMovement = bossRenderObject->getFinishMovement();
				if (bossFinishMovement) {
					(*spellCardBegin)->SpellCardWork();
				}
			}
			if ((*spellCardBegin)->getIsFinish() || bossRenderObject->getSpellCardHitPointClear()) {
				auto item = (*spellCardBegin)->getDropItem();
				if (item != nullptr) {
					for (auto item : *item) {
						ItemHelper::GenerateItemGroup(bossRenderObject->getPosition(), item.count, (Item::ItemType)item.type, true);
					}
				}

				(*spellCardBegin)->SpellCardRelease();
				delete *spellCardBegin;
				RenderManager::getInstance()->TerminateAllBullet();
				spellCardGroup.erase(spellCardBegin);
				isNewSpellCard = true;
			}
			
		}
		else {
			haveSpellCardAddToQueue = true;
			taskFinish = true;
		}
	}
}


void Boss::TaskRelease()
{
	if (taskIsInit) {
		if (!haveSpellCardAddToQueue) {
			for (auto spellcard = spellCardGroup.begin(); spellcard != spellCardGroup.end(); spellcard++) {
				(*spellcard)->SpellCardRelease();
				delete *spellcard;
			}
			spellCardGroup.clear();
		}
		if (haveAddRenderObjectToQueue) {
			RenderManager::getInstance()->CleanRenderObject(currentUuid);
			RenderManager::getInstance()->CleanUserInterface(BossInfoInterfaceUuid);
			bossRenderObject = nullptr;
			haveAddRenderObjectToQueue = false;
		}
		else {
			bossRenderObject->Release();
			delete bossRenderObject;
			bossRenderObject = nullptr;
		}

		if (haveBossMusic) {
			AudioHelper::playFromBuffer(stageMusic);
			AudioHelper::stopByBuffer(bossMusic);
			alDeleteBuffers(1, &bossMusic);
		}
		taskIsInit = false;
	}
}
