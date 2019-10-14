#pragma once
#ifndef _NORMAL_STRIKE_H_
#define _NORMAL_STRIKE_H_
#include "IAttack.h"
class NormalStrike:public IAttack {
public:
	virtual void Init() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual void checkCollisonWithEnemy(EnemyObject* pEnemy) override;
};
#endif