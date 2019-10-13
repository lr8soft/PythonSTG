#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "../XCRender/RenderObject.h"
class Enemy :public RenderObject {
protected:

public:

	virtual void Init() override;
	virtual void Render() override;
	virtual void Release() override;

};
#endif