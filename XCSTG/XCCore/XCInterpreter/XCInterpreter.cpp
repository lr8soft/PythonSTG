#include "XCInterpreter.h"

XCInterpreter::XCInterpreter()
{
	pyLoader.initPythonEvon();
	scriptCore = pyLoader.importModule("script.XCCore");
}

void XCInterpreter::ScriptLaunch()
{
	auto launcher = pyLoader.getAttrib(scriptCore, "coreLauncher");
	PyObject_CallFunction(launcher, NULL);
}

void XCInterpreter::ScriptRelease()
{
	auto finalizer = pyLoader.getAttrib(scriptCore, "coreFinalizer");
	PyObject_CallFunction(finalizer, NULL);
	pyLoader.unloadPythonEvon();
}
