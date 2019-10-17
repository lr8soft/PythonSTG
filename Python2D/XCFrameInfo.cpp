#include "XCFrameInfo.h"
#include <GLFW/glfw3.h>
float XCFrameInfo::FrameBottom = -1.0f, XCFrameInfo::FrameTop = 1.0f, XCFrameInfo::FrameRight = 1.0f, XCFrameInfo::FrameLeft = -1.0f;
int  XCFrameInfo::ScreenWidth = 720, XCFrameInfo::ScreenHeight = 720;
int XCFrameInfo::keyUp = GLFW_KEY_UP, XCFrameInfo::keyDown = GLFW_KEY_DOWN,
	XCFrameInfo::keyLeft = GLFW_KEY_LEFT, XCFrameInfo::keyRight = GLFW_KEY_RIGHT,
	XCFrameInfo::keyShoot = GLFW_KEY_Z, XCFrameInfo::keyItem = GLFW_KEY_X, XCFrameInfo::keySlow = GLFW_KEY_LEFT_SHIFT;

float XCFrameInfo::defaultGravity = 0.2f;
std::string XCFrameInfo::ScreenOriginTitle;