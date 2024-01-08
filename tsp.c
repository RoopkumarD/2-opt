#include <python3.10/Python.h>

static PyObject *method_tsp(PyObject *self, PyObject *args) {}

static PyMethodDef TSPMethods[] = {{"tsp", method_tsp, METH_VARARGS, NULL},
                                   {NULL, NULL, 0, NULL}};

static struct PyModuleDef tspmodule = {PyModuleDef_HEAD_INIT, "tsp",
                                       "TSP module", -1, TSPMethods};

PyMODINIT_FUNC PyInit_tsp(void) {
  PyObject *module = PyModule_Create(&tspmodule);
  return module;
}
