#include "Boss.h"


Boss::Boss(std::string uid, std::vector<std::string>& targetUUID,std::string bName, int wFrame,
	std::string imagePath, glm::vec2 divideInfo, int standByRow, int walkRow, int attackRow):Task(uid,targetUUID, 1, 0, wFrame)
{
	bossName = bName;
	currentUuid = uid;
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
		auto spellCardBegin = spellCardGroup.begin();
		auto spellCardEnd = spellCardGroup.end();
		if (spellCardBegin != spellCardEnd) {
			if (!(*spellCardBegin)->getIsFinish()) {
				(*spellCardBegin)->SpellCardWork();
			}
			if ((*spellCardBegin)->getIsFinish()) {
				(*spellCardBegin)->SpellCardRelease();
				delete *spellCardBegin;
				spellCardGroup.erase(spellCardBegin);
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

		taskIsInit = false;
	}
}
