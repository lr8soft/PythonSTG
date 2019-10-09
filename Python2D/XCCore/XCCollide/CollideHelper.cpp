#include "CollideHelper.h"

CollideHelper::CollideHelper(Player * player)
{
	pPlayer = player;
}

void CollideHelper::checkCollisionWithBullet(Bullet * pBullet)
{
	float *pos = pPlayer->getPosition();
	float x = *(pos), y = *(pos+1);
	if (!pBullet->getIsFinishTime() && pBullet->BulletCollideWithPoint(x, y)) {
		pBullet->startFinishEffect();
		pPlayer->hurtPlayer();
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
