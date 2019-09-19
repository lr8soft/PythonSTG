#pragma once
#ifndef _XCGAME_TIMER_H_
#define _XCGAME_TIMER_H_
class XCGameTimer {
private:
	static bool IsPause, afterPause;
	float nowFrame = 0.0f, deltaFrame = 0.0f, lastTime = 0.0f, increaseRate=1.0f,fpsNow=0.0f;
	float lastFpsUpdate = 0.0f,frameCounter = 0.0f;
	long double accumulateTime = 0.0;
	bool FirstRun = true;
public:
	void Tick();
	void Tick(float nowFrame);
	void SetIncreaseRate(float rate);
	void Clear();
	void Pause();
	void Resume();
	void AfterResume();
	float getNowFrame();
	float getDeltaFrame();
	float getLastFrame();
	float getFPS();
	double getAccumlateTime();
};
#endif