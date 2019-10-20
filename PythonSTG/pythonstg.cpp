#include "XCFrame.h"
int main() {

	XCFrame *frame = XCFrame::getInstance();
	frame->FrameInit();
	frame->FrameLoop();
	frame->FrameFinalize();
}