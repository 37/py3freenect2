#include "../pyfreenect2.hpp"
#include <iostream>

using libfreenect2::Freenect2Device;
using libfreenect2::FrameListener;

PyObject *py_Freenect2Device_new(PyObject *self, PyObject *args) {
	char *serialNumber = NULL;
	if(!PyArg_ParseTuple(args, "s", &serialNumber))
		return NULL;

	// TODO Pipeline support
	Freenect2Device *device = getGlobalFreenect2().openDevice(serialNumber);
	return PyCapsule_New(device, "Freenect2Device", py_Freenect2Device_destroy);
}
void py_Freenect2Device_destroy(PyObject *deviceCapsule) {
	((Freenect2Device*) PyCapsule_GetPointer(deviceCapsule, "Freenect2Device"))->close();
}

PyObject *py_Freenect2Device_start(PyObject *self, PyObject *args) {
	PyObject *deviceCapsule = NULL;
	if(!PyArg_ParseTuple(args, "O", &deviceCapsule))
		return NULL;
	((Freenect2Device*) PyCapsule_GetPointer(deviceCapsule, "Freenect2Device"))->start();
	Py_INCREF(Py_None);
	return Py_None;
}
PyObject *py_Freenect2Device_stop(PyObject *self, PyObject *args) {
	PyObject *deviceCapsule = NULL;
	if(!PyArg_ParseTuple(args, "O", &deviceCapsule))
		return NULL;
	((Freenect2Device*) PyCapsule_GetPointer(deviceCapsule, "Freenect2Device"))->stop();
	Py_INCREF(Py_None);
	return Py_None;
}

PyObject *py_Freenect2Device_setColorFrameListener(PyObject *self, PyObject *args) {
	PyObject *deviceCapsule = NULL;
	PyObject *listenerCapsule = NULL;
	if(!PyArg_ParseTuple(args, "OO", &deviceCapsule, &listenerCapsule))
		return NULL;
	Freenect2Device *device = (Freenect2Device*) PyCapsule_GetPointer(deviceCapsule, "Freenect2Device");

	std::cout << "device in F2D.cpp: " << device << std::endl;
	std::cout << "listenercapsule in F2D.cpp: " << listenerCapsule << std::endl;
	Py_INCREF(listenerCapsule);
	FrameListener *listener = (FrameListener*) PyCapsule_GetPointer(listenerCapsule, "SyncMultiFrameListener");

	///// BOOO!!!
	std::cout << "listener in F2D.cpp: " << listener << std::endl;
	device->setColorFrameListener(listener);
	Py_INCREF(Py_None);
	return Py_None;
}
PyObject *py_Freenect2Device_setIrAndDepthFrameListener(PyObject *self, PyObject *args) {
	PyObject *deviceCapsule = NULL;
	PyObject *listenerCapsule = NULL;
	if(!PyArg_ParseTuple(args, "OO", &deviceCapsule, &listenerCapsule))
		return NULL;
	Freenect2Device *device = (Freenect2Device*) PyCapsule_GetPointer(deviceCapsule, "Freenect2Device");
	Py_INCREF(listenerCapsule);
	FrameListener *listener = (FrameListener*) PyCapsule_GetPointer(listenerCapsule, "SyncMultiFrameListener");
	device->setIrAndDepthFrameListener(listener);
	Py_INCREF(Py_None);
	return Py_None;
}

PyObject *py_Freenect2Device_getSerialNumber(PyObject *self, PyObject *args) {
	PyObject *deviceCapsule = NULL;
	if(!PyArg_ParseTuple(args, "O", &deviceCapsule))
		return NULL;
	Freenect2Device *device = (Freenect2Device*) PyCapsule_GetPointer(deviceCapsule, "Freenect2Device");
	std::string serialNumber = device->getSerialNumber();
	return PyUnicode_FromString(serialNumber.c_str());
}
PyObject *py_Freenect2Device_getFirmwareVersion(PyObject *self, PyObject *args) {
	PyObject *deviceCapsule = NULL;
	if(!PyArg_ParseTuple(args, "O", &deviceCapsule))
		return NULL;
	Freenect2Device *device = (Freenect2Device*) PyCapsule_GetPointer(deviceCapsule, "Freenect2Device");
	std::string firmwareVersion = device->getFirmwareVersion();
	return PyUnicode_FromString(firmwareVersion.c_str());
}

PyObject *py_Freenect2Device_getColorCameraParams(PyObject *self, PyObject *args) {
	PyObject *deviceCapsule = NULL;
	if(!PyArg_ParseTuple(args, "O", &deviceCapsule))
		return NULL;
	Freenect2Device *device = (Freenect2Device*) PyCapsule_GetPointer(deviceCapsule, "Freenect2Device");
	Freenect2Device::ColorCameraParams *colorCameraParams = new Freenect2Device::ColorCameraParams;
	return PyCapsule_New(colorCameraParams, "ColorCameraParams", py_Freenect2Device_ColorCameraParams_destroy);
}
PyObject *py_Freenect2Device_getIRCameraParams(PyObject *self, PyObject *args) {
	PyObject *deviceCapsule = NULL;
	if(!PyArg_ParseTuple(args, "O", &deviceCapsule))
		return NULL;
	Freenect2Device *device = (Freenect2Device*) PyCapsule_GetPointer(deviceCapsule, "Freenect2Device");
	Freenect2Device::IrCameraParams *irCameraParams = new Freenect2Device::IrCameraParams;
	return PyCapsule_New(irCameraParams, "IRCameraParams", py_Freenect2Device_IRCameraParams_destroy);
}

void py_Freenect2Device_ColorCameraParams_destroy(PyObject *colorCameraParamsCapsule) {
	delete ((Freenect2Device::ColorCameraParams*) PyCapsule_GetPointer(colorCameraParamsCapsule, "ColorCameraParams"));
}
void py_Freenect2Device_IRCameraParams_destroy(PyObject *irCameraParamsCapsule) {
	delete ((Freenect2Device::IrCameraParams*) PyCapsule_GetPointer(irCameraParamsCapsule, "IRCameraParams"));
}
