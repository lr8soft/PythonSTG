#pragma once
#ifndef _XCFrameInfo_H_
#define _XCFrameInfo_H_
#include <string>
class XCFrameInfo {
public:
	static float FrameBottom , FrameTop, FrameRight, FrameLeft;
	static int ScreenWidth, ScreenHeight;
	static std::string ScreenOriginTitle;

	static int keyUp, keyDown, keyLeft, keyRight, keyShoot, keyItem, keySlow, keyItem2;
	static float defaultGravity;
};
#endif