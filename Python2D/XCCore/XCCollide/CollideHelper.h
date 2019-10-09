#pragma once
#ifndef _COLLIDE_HELPER_H_
#define _COLLIDE_HELPER_H_
#include "../Item/Player.h"
#include "../Bullet/Bullet.h"
class CollideHelper {
private:
	Player* pPlayer;
public:
	CollideHelper(Player *player);
	void checkCollisionWithBullet(Bullet *pBullet);
	float* getPlayerPosition();
};
#endif