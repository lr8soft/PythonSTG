#include "PauseMenu.h"

void PauseMenu::checkKeyInput()
{
}

PauseMenu::PauseMenu()
{
}

void PauseMenu::Init()
{
	if (!isInit) {
		isInit = true;
	}
}

void PauseMenu::Render()
{
	if (isInit) {
	
	}
}

void PauseMenu::Release()
{
	if (isInit) {
	
		isInit = false;
	}
}
