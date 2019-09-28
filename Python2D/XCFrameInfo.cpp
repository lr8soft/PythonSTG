#include "XCFrameInfo.h"
#include <GLFW/glfw3.h>
float XCFrameInfo::FrameBottom = -1.0f, XCFrameInfo::FrameTop = 1.0f, XCFrameInfo::FrameRight = 1.0f, XCFrameInfo::FrameLeft = -1.0f;
int XCFrameInfo::gameWidth = 640, XCFrameInfo::gameHeight = 640;
int XCFrameInfo::p1_keyUp = GLFW_KEY_UP, XCFrameInfo::p1_keyDown = GLFW_KEY_DOWN,
	XCFrameInfo::p1_keyLeft = GLFW_KEY_LEFT, XCFrameInfo::p1_keyRight = GLFW_KEY_RIGHT,
	XCFrameInfo::p1_keyShoot = GLFW_KEY_Z, XCFrameInfo::p1_keyItem = GLFW_KEY_X, XCFrameInfo::p1_keySlow = GLFW_KEY_LEFT_SHIFT;