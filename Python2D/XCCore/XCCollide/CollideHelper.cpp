#include "CollideHelper.h"

CollideHelper::CollideHelper(Player * player)
{
	pPlayer = player;
}

void CollideHelper::checkCollisionWithBullet(Bullet * pBullet)
{
	float *pos = pPlayer->getPosition();
	float x = *(pos), y = *(pos+1);
	if (pBullet->BulletCollideWithPoint(x, y)) {
		pBullet->startFinishEffect();
		pPlayer->hurtPlayer();
	}
}
