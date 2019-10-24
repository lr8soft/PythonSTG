#include "Boss.h"
#include "../XCRender/XCImageHelper.h"
#include "../XCRender/RenderManager.h"
#include "../UserInterface/BossInfoInterface.h"
Boss::Boss(std::string uid, std::vector<std::string>& targetUUID,std::string bName, int wFrame,
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
}

void Boss::AddSpellCard(SpellCard * spellcard)
{
	spellCardGroup.push_back(spellcard);
}

void Boss::TaskInit()
{
	if (!taskIsInit) {
		for (auto spellcard = spellCardGroup.begin(); spellcard != spellCardGroup.end(); spellcard++) {
			(*spellcard)->SpellCardInit();
		}
		XCImageHelper* image = new XCImageHelper(imagePath, true);
		bossRenderObject = new BossObject(image, divideInfo, scaleInfo, standByRow, walkRow, attackRow);
		taskIsInit = true;
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
					BossInfoInterface::getInstance()->setSpellCardCount(spellCardGroup.size()+11);
					BossInfoInterface::getInstance()->setSpellCardName((*spellCardBegin)->getSpellCardName());

					bossRenderObject->setBossHitPoint((*spellCardBegin)->getSpellCardHitPoint());
					bossRenderObject->setBossSpellCardCount(spellCardGroup.size());
					bossRenderObject->setBossSpellCardTime((*spellCardBegin)->getSpellCardTime());
					bossRenderObject->setMovement((*spellCardBegin)->getMovement());
					isNewSpellCard = false;
				}
				(*spellCardBegin)->SpellCardWork();
			
			}
			if ((*spellCardBegin)->getIsFinish()) {
				(*spellCardBegin)->SpellCardRelease();
				delete *spellCardBegin;
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

		bossRenderObject->Release();
		delete bossRenderObject;
		taskIsInit = false;
	}
}
