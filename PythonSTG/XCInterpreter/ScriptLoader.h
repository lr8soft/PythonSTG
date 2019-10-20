#pragma once
#ifndef _script_loader_h_
#define _script_loader_h_
#include <iostream>
#include <Python.h>
#include <string>
#include <initializer_list>
class ScriptLoader {
private:
	static bool have_python_init;
public:
	PyObject* importModule(std::string name);
	PyObject* getAttrib(PyObject* obj, std::string attribName);
	PyObject* callObjectMethod(PyObject * object, std::string funcName, const char *format);//const char *format, ...);
	PyObject* callFunction(PyObject* module, std::string funcName, const char *format);
	static void initPythonEvon();
	static void unloadPythonEvon();
	static void appendModuleToEvon(std::string path);

	template <typename _Ty>
	static _Ty getSingleArg(PyObject* ret) {
		static _Ty returnValue;
		std::string format;
		if (std::is_same<int,_Ty>::value) {
			format = "i";
		}
		else if (std::is_same<char, _Ty>::value) {
			format = "b";
		}
		else if (std::is_same<const char*, _Ty>::value) {//std::string的请原地去世
			format = "s";
		}
		else if (std::is_same<float, _Ty>::value) {
			format = "f";
		}
		else if (std::is_same<double, _Ty>::value) {
			format = "d";
		}
		else if (std::is_same<long, _Ty>::value) {
			format = "l";
		}
		else if (std::is_same<short, _Ty>::value) {
			format = "h";
		}
		else if (std::is_same<PyObject *, _Ty>::value) {
			format = "O";
		}
		else {
			format = "O";//PyObject*
		}
		PyArg_Parse(ret, format.c_str(), &returnValue);
		return returnValue;
	}
};
#define MultiThreadDefine \
int nHold = PyGILState_Check(); \
PyGILState_STATE gstate; \
if (!nHold) \
{ \
gstate = PyGILState_Ensure(); \
} \
Py_BEGIN_ALLOW_THREADS;\
Py_BLOCK_THREADS;\


#define MultiThreadDefineEnd \
Py_UNBLOCK_THREADS;\
Py_END_ALLOW_THREADS;\
if (!nHold)\
{\
	PyGILState_Release(gstate);\
}\

#endif

