#pragma once
#ifndef _script_loader_h_
#define _script_loader_h_
#include <iostream>
#include <Python.h>
class ScriptLoader {
private:
	static bool have_python_init;
public:
	PyObject* importModule(std::string name);
	PyObject* getAttrib(PyObject* obj, std::string attribName);
	static void initPythonEvon();
	static void unloadPythonEvon();
	static void appendModuleToEvon(std::string path);
};
#endif

