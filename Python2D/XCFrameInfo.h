#pragma once
#ifndef _XCFrameInfo_H_
#define _XCFrameInfo_H_
#include <string>
class XCFrameInfo {
public:
	static float FrameBottom , FrameTop, FrameRight, FrameLeft;
	static int ScreenWidth, ScreenHeight;
	static std::string ScreenOriginTitle;

	static int p1_keyUp, p1_keyDown, p1_keyLeft, p1_keyRight, p1_keyShoot, p1_keyItem, p1_keySlow;
	static float defaultGravity;
};
#endif