#include "ScriptLoader.h"
bool ScriptLoader::have_python_init = false;

PyObject * ScriptLoader::importModule(std::string name)
{
	PyObject* modulePtr = nullptr;
	if (have_python_init) {
		modulePtr = PyImport_ImportModule(name.c_str());
	}
	else {
		std::cout << "[ERROR]Python environment haven\'t loaded." << std::endl;
	}
	return modulePtr;
}

PyObject * ScriptLoader::getAttrib(PyObject * obj, std::string attribName)
{
	PyObject* attrib = nullptr;
	if (obj == nullptr) {
		std::cout << "[ERROR]Pointer to pyobject is null." << std::endl;
	}
	else {
		attrib = PyObject_GetAttrString(obj, attribName.c_str());
	}
	
	return attrib;
}

PyObject * ScriptLoader::callObjectMethod(PyObject * object, std::string funcName, const char *format)
{
	PyObject* returnValue = nullptr;
	if (object == nullptr) {
		std::cout << "[ERROR]Pointer to pyobject is null." << std::endl;
	}
	else {
		returnValue = PyObject_CallMethod(object, funcName.c_str(), format);
		if (returnValue==nullptr) {
			;//std::cout << "[INFO] Function " + funcName + " haven't return value!" << std::endl;
		}
	}
	return returnValue;
}

PyObject * ScriptLoader::callFunction(PyObject * module, std::string funcName, const char * format)
{
	PyObject* returnValue = nullptr;
	if (module == nullptr) {
		std::cout << "[ERROR]Pointer to pyobject is null." << std::endl;
	}
	else {
		returnValue = PyEval_CallFunction(module, funcName.c_str(), format);
		if (returnValue == nullptr) {
			;//std::cout << "[INFO] Function " + funcName + " haven't return value!" << std::endl;
		}
	}
	return returnValue;
}


void ScriptLoader::initPythonEvon()
{
	if (!have_python_init) {//First time init.
		Py_Initialize();

		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('./')");//Load all script
		if (Py_IsInitialized()) {
			have_python_init = true;
		}
		else {
			PyEval_InitThreads();
			int nInit = PyEval_ThreadsInitialized();
			if (nInit)
			{
				PyEval_SaveThread();
			}
			else {
				std::cout << "[ERROR]Failed to init multi-thread." << std::endl;
			}
			std::cout << "[ERROR]Failed to init python environment." << std::endl;
		}
	}
}

void ScriptLoader::unloadPythonEvon()
{
	if (have_python_init) {
		PyGILState_Ensure();
		Py_Finalize();
		have_python_init = false;
	}
}

void ScriptLoader::appendModuleToEvon(std::string path)
{
	if (have_python_init) {
		PyRun_SimpleString(("sys.path.append('" + path + "./')").c_str());
	}
}


