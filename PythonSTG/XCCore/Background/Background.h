#pragma once
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
class Background {
public:
	virtual void BackgroundInit() = 0;
	virtual void BackgroundRender() = 0;
	virtual void BackgroundRelease() = 0;
};
#endif