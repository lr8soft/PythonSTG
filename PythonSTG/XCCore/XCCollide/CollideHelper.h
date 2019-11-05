#pragma once
#ifndef _COLLIDE_HELPER_H_
#define _COLLIDE_HELPER_H_
#include "../Player/Player.h"
#include "../Bullet/Bullet.h"
class CollideHelper {
private:
	Player* pPlayer;

	long nowScore = 0;
	long nowGraze = 0;
	long nowMoonPoint = 0;

public:
	CollideHelper(Player *player);
	void checkCollisionWithBullet(Bullet *pBullet);
	float* getPlayerPosition();

	void addPlayerLife();
	void addPlayerBomb();
	void addPlayerPoint();
	void addPlayerPower();
	void addPlayerMoonPoint();

	bool getPlayerIsMoonState();
};
#endif