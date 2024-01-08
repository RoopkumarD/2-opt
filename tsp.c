#include "utils.h"

static PyObject *method_tsp(PyObject *self, PyObject *args) {
  PyObject *nodes;
  PyObject *nodes_weights;

  if (!PyArg_ParseTuple(args, "OO", &nodes, &nodes_weights)) {
    return NULL;
  }

  Py_ssize_t nodes_length = PyList_Size(nodes);
  int *arr = (int *)malloc(nodes_length * sizeof(int));

  if (arr == NULL) {
    puts("Wasn't able to allocate memory");
    return PyLong_FromLong(1);
  }

  srand(time(NULL));
  hill_climb(arr, nodes_length, nodes_weights);

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
