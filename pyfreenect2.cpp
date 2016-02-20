#include "Python.h"
#include "pyfreenect2.hpp"
#include <iostream>

struct module_state {
	PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif

static PyObject *
error_out(PyObject *m) {
	struct module_state *st = GETSTATE(m);
	PyErr_SetString(st->error, "something bad happened");
	return NULL;
}

static int pyfreenect2_traverse(PyObject *m, visitproc visit, void *arg) {
	Py_VISIT(GETSTATE(m)->error);
	return 0;
}

static int pyfreenect2_clear(PyObject *m) {
	Py_CLEAR(GETSTATE(m)->error);
	return 0;
}

static PyMethodDef pyfreenect2_methods[] = {
	// Freenect2
	{ "numberOfDevices", py_numberOfDevices, METH_VARARGS, NULL },
	{ "getDefaultDeviceSerialNumber", py_getDefaultDeviceSerialNumber, METH_VARARGS, NULL },
	// Freenect2Device
	{ "Freenect2Device_new", py_Freenect2Device_new, METH_VARARGS, NULL },
	{ "Freenect2Device_start", py_Freenect2Device_start, METH_VARARGS, NULL },
	{ "Freenect2Device_stop", py_Freenect2Device_stop, METH_VARARGS, NULL },
	{ "Freenect2Device_setColorFrameListener", py_Freenect2Device_setColorFrameListener, METH_VARARGS, NULL },
	{ "Freenect2Device_setIrAndDepthFrameListener", py_Freenect2Device_setIrAndDepthFrameListener, METH_VARARGS, NULL },
	{ "Freenect2Device_getSerialNumber", py_Freenect2Device_getSerialNumber, METH_VARARGS, NULL },
	{ "Freenect2Device_getFirmwareVersion", py_Freenect2Device_getFirmwareVersion, METH_VARARGS, NULL },
	{ "Freenect2Device_getColorCameraParams", py_Freenect2Device_getColorCameraParams, METH_VARARGS, NULL },
	{ "Freenect2Device_getIRCameraParams", py_Freenect2Device_getIRCameraParams, METH_VARARGS, NULL },
	// SyncMultiFrameListener
	{ "SyncMultiFrameListener_new", py_SyncMultiFrameListener_new, METH_VARARGS, NULL },
	{ "SyncMultiFrameListener_waitForNewFrame", py_SyncMultiFrameListener_waitForNewFrame, METH_VARARGS, NULL },
	// Registration
	{ "Registration_new", py_Registration_new, METH_VARARGS, NULL },
	{ "Registration_apply", py_Registration_apply, METH_VARARGS, NULL },
	// FrameMap
	{ "FrameMap_getFrame", py_FrameMap_getFrame, METH_VARARGS, NULL },
	// Frame
	{ "Frame_getHeight", py_Frame_getHeight, METH_VARARGS, NULL },
	{ "Frame_getWidth", py_Frame_getWidth, METH_VARARGS, NULL },
	{ "Frame_getData", py_Frame_getData, METH_VARARGS, NULL },
	{ "Frame_getDepthData", py_Frame_getDepthData, METH_VARARGS, NULL },
	// Sentinel
	{ NULL, NULL, 0, NULL}
};

static struct PyModuleDef pyfreenect2_module = {
	PyModuleDef_HEAD_INIT,
	"_pyfreenect2",
	NULL,
	sizeof(struct module_state),
	pyfreenect2_methods,
	NULL,
	pyfreenect2_traverse,
	pyfreenect2_clear,
	NULL
};

PyMODINIT_FUNC
PyInit__pyfreenect2() {

  /// enables debug of libfreenect2
  /// libfreenect2::setGlobalLogger(libfreenect2::createConsoleLogger(libfreenect2::Logger::Debug));

  import_array();
  return PyModule_Create(&pyfreenect2_module);
  import_array();
}
