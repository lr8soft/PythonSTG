#include "XCFrame.h"
#ifndef _DEBUG
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif
int main() {
	XCFrame *frame = XCFrame::getInstance();
	frame->FrameInit();
	frame->FrameLoop();
	frame->FrameFinalize();
}