#pragma once
#ifndef _RENDER_OBJECT_H_
#define _RENDER_OBJECT_H_
class RenderObject {
protected:
	bool isWorkFinish = false;
public:
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	inline bool getIsTerminate() {
		return isWorkFinish;
	}
};
#endif