#include "utils.h"
#include <stdio.h>

static PyObject *method_tsp(PyObject *self, PyObject *args) {
  PyObject *nodes;
  PyObject *nodes_weights;

  if (!PyArg_ParseTuple(args, "OO", &nodes, &nodes_weights)) {
    return NULL;
  }

  printf("%lu\n", get_elem(nodes_weights, 0, 0));

  Py_ssize_t nodes_length = PyList_Size(nodes);
  for (Py_ssize_t i = 0; i < nodes_length; i++) {
    printf("%s\n", PyUnicode_AsUTF8(PyList_GetItem(nodes, i)));
  }

  return PyLong_FromLong(0);
}

static PyMethodDef TSPMethods[] = {{"tsp", method_tsp, METH_VARARGS, NULL},
                                   {NULL, NULL, 0, NULL}};

static struct PyModuleDef tspmodule = {PyModuleDef_HEAD_INIT, "tsp",
                                       "TSP module", -1, TSPMethods};

PyMODINIT_FUNC PyInit_tsp(void) {
  PyObject *module = PyModule_Create(&tspmodule);
  return module;
}
