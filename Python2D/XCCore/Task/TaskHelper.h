#pragma once
#ifndef _TASKHELPER_H_
#define _TASKHELPER_H_
#include <Python.h>
#include <string>
#include "TaskInsideUnit.h"
#include "Task.h"
class TaskHelper {
public:
	static TaskInsideUnit* parseTaskUnitFromObject(std::string parentUuid, PyObject* unitObject);
	static Task* parseTaskFromObject(PyObject* taskObject);
};
#endif