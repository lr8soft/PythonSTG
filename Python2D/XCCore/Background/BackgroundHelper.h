#pragma once
#ifndef _BACKGROUND_HELPER_H_
#define _BACKGROUND_HELPER_H_
#include "Background.h"
class BackgroundHelper {
public:
	static Background* getBackgroundByID(int id);
};
#endif