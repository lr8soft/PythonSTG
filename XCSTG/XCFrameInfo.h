#pragma once
#ifndef _XCFrameInfo_H_
#define _XCFrameInfo_H_
class XCFrameInfo {
public:
	static float FrameBottom , FrameTop, FrameRight, FrameLeft;
	static int gameWidth, gameHeight;/*3:4*/

	static int p1_keyUp, p1_keyDown, p1_keyLeft, p1_keyRight, p1_keyShoot, p1_keyItem, p1_keySlow;
};
#endif