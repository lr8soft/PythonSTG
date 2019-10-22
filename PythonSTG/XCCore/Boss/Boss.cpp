#include "Boss.h"

void Boss::taskSubWork()
{
}

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
}

void Boss::TaskRelease()
{
}
