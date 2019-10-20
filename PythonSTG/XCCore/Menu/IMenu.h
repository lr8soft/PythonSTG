#pragma once
#ifndef _IMENU_H_
#define _IMENU_H_
#include "../XCRender/RenderObject.h"
constexpr auto MenuUniformUUID = "MenuItemUniformUUID";
class IMenu:public RenderObject {
public:
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};

#endif