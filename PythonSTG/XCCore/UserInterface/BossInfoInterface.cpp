#include "BossInfoInterface.h"
BossInfoInterface* BossInfoInterface::pInstance = nullptr;
BossInfoInterface::BossInfoInterface()
{
}

BossInfoInterface * BossInfoInterface::getInstance()
{
	if (pInstance == nullptr) {
		pInstance = new BossInfoInterface;
	}
	return pInstance;
}

void BossInfoInterface::UserInterfaceInit()
{
	if (!isInit) {
	
		isInit = true;
	}
}

void BossInfoInterface::UserInterfaceRender()
{
	if (isInit) {
	
	}
}

void BossInfoInterface::UserInterfaceRelease()
{
	if (isInit) {
		delete pInstance;
		pInstance = nullptr;
		isInit = false;
	}
}
