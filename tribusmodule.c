#include <Python.h>

#include "tribus.h"

static PyObject *tribus_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    tribushashm((char *)PyBytes_AsString((PyObject*) input), output);
#else
    tribushashm((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef TribusMethods[] = {
    { "getPoWHash", tribus_getpowhash, METH_VARARGS, "Returns the proof of work hash using tribus hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef TribusModule = {
    PyModuleDef_HEAD_INIT,
    "tribushashm",
    "...",
    -1,
    TribusMethods
};

PyMODINIT_FUNC PyInit_tribushashm(void) {
    return PyModule_Create(&TribusModule);
}

#else

PyMODINIT_FUNC inittribushashm(void) {
    (void) Py_InitModule("tribushashm", TribusMethods);
}
#endif
