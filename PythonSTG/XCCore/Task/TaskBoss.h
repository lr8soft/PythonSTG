#pragma once
#ifndef _TASK_BOSS_H_
#define _TASK_BOSS_H_
#include "TaskInsideUnit.h"
#include "Task.h"
class TaskBoss :public Task{
	virtual void taskSubWork() override;
public:
	virtual void TaskInit() override;
	virtual void TaskRelease() override;
};
#endif