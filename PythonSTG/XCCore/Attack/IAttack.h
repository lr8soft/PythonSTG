#pragma once
#ifndef _IATTACK_H_
#define _IATTACK_H_
#include "../XCRender/RenderObject.h"
#include "../Enemy/EnemyObject.h"
#include "../Boss/BossObject.h"
class IAttack:public RenderObject {
protected:

public:
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	virtual void checkCollisionWithEnemy(EnemyObject* pEnemy) = 0;
	virtual void checkCollisionWithBoss(BossObject* pBoss) = 0;
	/*
	inline bool getIsTerminate() {
		return isWorkFinish;
	}

	ObjectType getCurrentType() {
		return objectType;
	}
	*/
};
#endif