#pragma once
#ifndef _IUSER_INTERFACE_H_
#define _IUSER_INTERFACE_H_
class IUserInterface {
protected:
	bool isInit = false, workFinish = false;
public:
	virtual void UserInterfaceInit() = 0;
	virtual void UserInterfaceRender() = 0;
	virtual void UserInterfaceRelease() = 0;

	bool getIsInit() {
		return isInit;
	}

	bool getIsWorkFinish() {
		return workFinish;
	}
};
#endif