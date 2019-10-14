#pragma once
#ifndef _IATTACK_H_
#define _IATTACK_H_
#include "../Enemy/EnemyObject.h"
class IAttack {
public:
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	virtual void checkCollisonWithEnemy(EnemyObject* pEnemy) = 0;
};
#endif