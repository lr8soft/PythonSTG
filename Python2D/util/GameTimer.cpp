#include "GameTimer.h"
#include <glfw/glfw3.h>
#include <iostream>
bool XCGameTimer::IsPause = false;
bool XCGameTimer::afterPause = false;
void XCGameTimer::Tick()
{
	if (!IsPause) 
	{
		if (afterPause)
		{
			nowFrame = glfwGetTime();
			lastTime = nowFrame;
			deltaFrame = 0.0f;
			afterPause = false;
			return;
		}
		if (!FirstRun) {//Not first run
			nowFrame = glfwGetTime();
			deltaFrame = (nowFrame - lastTime)*increaseRate;
			lastTime += deltaFrame;
		}
		else {
			nowFrame = glfwGetTime();
			deltaFrame = 0;
			lastTime = nowFrame;
			lastFpsUpdate = lastTime;
			FirstRun = false;
		}
		frameCounter++;
		if (lastTime - lastFpsUpdate >= 1) {
			lastFpsUpdate = lastTime;
			fpsNow = frameCounter;
			frameCounter = 0;
		}
		accumulateTime += deltaFrame;
	}
}

void XCGameTimer::Tick(float update_nowFrame)
{
	if (!IsPause) 
	{
		if (afterPause)
		{
			nowFrame = update_nowFrame;
			lastTime = update_nowFrame;
			deltaFrame = 0.0f;
			return;
		}
		if (!FirstRun) {//Not first run
			nowFrame = update_nowFrame;
			deltaFrame = (nowFrame - lastTime)*increaseRate;
			lastTime += deltaFrame;
		}
		else {
			nowFrame = update_nowFrame;
			deltaFrame = 0;
			lastTime = nowFrame;
			lastFpsUpdate = lastTime;
			FirstRun = false;
		}
		frameCounter++;
		if (lastTime - lastFpsUpdate >= 1) {
			lastFpsUpdate = lastTime;
			fpsNow = frameCounter;
			frameCounter = 0;
		}
		accumulateTime += deltaFrame;
	}
}

void XCGameTimer::SetIncreaseRate(float rate)
{
	increaseRate = rate;
}

void XCGameTimer::Clear()
{
	fpsNow = 0.0f;
	frameCounter = 0.0f;
	nowFrame = 0.0f;
	deltaFrame = 0.0f;
	lastTime = 0.0f;
	lastFpsUpdate = 0.0f;
	accumulateTime = 0.0;
	increaseRate = 1.0f;
	FirstRun = true;
}

void XCGameTimer::Pause()
{
	IsPause = true;
}

void XCGameTimer::Resume()
{
	IsPause = false;
	afterPause = true;
}

void XCGameTimer::AfterResume()
{
	afterPause = false;
}

float XCGameTimer::getNowFrame()
{
	return nowFrame;
}

float XCGameTimer::getDeltaFrame()
{
	return deltaFrame;
}

float XCGameTimer::getLastFrame()
{
	return lastTime;
}

float XCGameTimer::getFPS()
{
	return fpsNow;
}

double XCGameTimer::getAccumlateTime()
{
	return accumulateTime;
}
