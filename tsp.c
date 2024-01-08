#include "utils.h"
#include <stdio.h>

static PyObject *method_tsp(PyObject *self, PyObject *args) {
  PyObject *nodes;
  PyObject *nodes_weights;

  printf("before parsing the args");
  if (!PyArg_ParseTuple(args, "OO", &nodes, &nodes_weights)) {
    return NULL;
  }
  printf("after parsing the args");

  Py_ssize_t nodes_length = PyList_Size(nodes);
  printf("before allocating memory");
  int *arr = (int *)malloc(nodes_length * sizeof(int));
  printf("after allocating memory");
  if (arr == NULL) {
    printf("Wasn't able to allocate memory");
    return PyLong_FromLong(1);
  }

  printf("before hill_climb");
  srand(time(NULL));
  hill_climb(arr, nodes_length, nodes_weights);
  printf("after hill_climb");

  for (int i = 0; i < nodes_length; i++) {
    printf("%i\n", arr[i]);
  }

  free(arr);

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
