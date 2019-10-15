#pragma once
#ifndef _RENDER_OBJECT_H_
#define _RENDER_OBJECT_H_
class RenderObject {
public:
	enum ObjectType {
		BulletType = 0, ItemType, EnemyType, AttackType, NoneType
	};

protected:
	ObjectType objectType = NoneType;

	void setCurrentType(ObjectType type) {
		objectType = type;
	}

	bool isWorkFinish = false;
public:
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	inline bool getIsTerminate() {
		return isWorkFinish;
	}

	ObjectType getCurrentType() {
		return objectType;
	}
};
#endif