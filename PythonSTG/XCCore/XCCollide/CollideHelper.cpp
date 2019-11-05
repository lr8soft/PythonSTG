#include "CollideHelper.h"

CollideHelper::CollideHelper(Player * player)
{
	pPlayer = player;
}

void CollideHelper::checkCollisionWithBullet(Bullet * pBullet)
{
	float *pos = pPlayer->getPosition();
	float x = *(pos), y = *(pos+1);
	bool haveGraze = false, haveCollide = false;
	if (!pBullet->getIsTerminate() && pBullet->BulletCollideWithPoint(x, y, haveGraze)) {
		pBullet->setBulletTerminate();
		pPlayer->hurtPlayer();
		haveCollide = true;
	}
	if (haveGraze && !haveCollide) {
		nowGraze++;
		pPlayer->grazePlayer();
	}
}

float * CollideHelper::getPlayerPosition()
{
	float *srcPostion = pPlayer->getPosition();

	static float position[3];
	position[0] = *(srcPostion);
	position[1] = *(srcPostion + 1);
	position[2] = *(srcPostion + 2);
	return position;
}

void CollideHelper::addPlayerLife()
{
	pPlayer->addLife();
}

void CollideHelper::addPlayerBomb()
{
	pPlayer->addBomb();
}

void CollideHelper::addPlayerPoint()
{
	pPlayer->addPoint();
}

void CollideHelper::addPlayerPower()
{
	pPlayer->addPower();
}

void CollideHelper::addPlayerMoonPoint()
{
	pPlayer->addMoonPoint();
}
