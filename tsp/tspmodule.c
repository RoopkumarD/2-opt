#include "utils.h"

static PyObject *method_tsp2opt(PyObject *self, PyObject *args) {
  PyObject *nodes_weights;
  int repeat = 1;

  if (!PyArg_ParseTuple(args, "O|i", &nodes_weights, &repeat)) {
    return NULL;
  }

  // defining all required variables
  int *final_arr = NULL;
  PyObject *lst = NULL;
  PyObject *cost_obj = NULL;
  PyObject *dict = NULL;

  // Input validation
  // checking if repeat is greater than 1 or equal
  if (repeat < 1) {
    PyErr_SetString(PyExc_ValueError,
                    "repeat must be equal to or greater than 1");
    goto error_cleanup;
  }
  // checking if nodes_weights is 2x2 square matrix, with inputs as integers
  // first checking if outer object is list
  if (!PyList_Check(nodes_weights)) {
    PyErr_SetString(PyExc_TypeError, "nodes_weights must be a list");
    goto error_cleanup;
  }
  // checking if it has some elem or not
  Py_ssize_t nodes_length = PyList_Size(nodes_weights);
  if (nodes_length <= 0) {
    PyErr_SetString(PyExc_ValueError,
                    "nodes_weights must not be an empty list");
    goto error_cleanup;
  }
  // then checking inside is list
  // checking if inner list has same length
  for (int i = 0; i < nodes_length; i++) {
    PyObject *inner = PyList_GetItem(nodes_weights, i);
    if (!PyList_Check(inner)) {
      PyErr_SetString(PyExc_TypeError,
                      "Inner elements of nodes_weights must be lists");
      goto error_cleanup;
    }
    if (PyList_Size(inner) != nodes_length) {
      PyErr_SetString(PyExc_ValueError,
                      "Inner lists of nodes_weights must have the same length");
      goto error_cleanup;
    }
    for (int j = 0; j < nodes_length; j++) {
      if (!PyLong_Check(PyList_GetItem(inner, j))) {
        PyErr_SetString(
            PyExc_TypeError,
            "Inner elements inside nodes_weights must be of type number");
        goto error_cleanup;
      }
    }
  }

  srand(time(NULL));
  // setting big number initially
  long current_cost = 2147483000;

  for (int i = 0; i < repeat; i++) {
    int *arr = (int *)malloc(nodes_length * sizeof(int));
    if (arr == NULL) {
      PyErr_SetString(PyExc_MemoryError,
                      "Failed to allocate memory for temporary array");
      goto error_cleanup;
    }

    hill_climb(arr, nodes_length, nodes_weights);
    long cost = get_cost(nodes_weights, arr, nodes_length);
    if (cost < current_cost) {
      free(final_arr);
      current_cost = cost;
      final_arr = arr;
    } else {
      free(arr);
    }
  }

  // building the order
  lst = PyList_New(nodes_length);
  if (lst == NULL) {
    PyErr_SetString(PyExc_MemoryError,
                    "Failed to create a new temp Python list");
    goto error_cleanup;
  }
  for (int i = 0; i < nodes_length; i++) {
    // adding elem in list
    PyObject *elem = PyLong_FromLong(final_arr[i]);
    if (elem == NULL) {
      PyErr_SetString(PyExc_MemoryError,
                      "Failed to create a new temp elem variable");
      goto error_cleanup;
    }
    PyList_SetItem(lst, i, elem);
  }

  // combining results in dict
  dict = PyDict_New();
  if (dict == NULL) {
    PyErr_SetString(PyExc_MemoryError, "Failed to create return dict");
    goto error_cleanup;
  }
  if (PyDict_SetItemString(dict, "order", lst) == -1) {
    PyErr_SetString(PyExc_RuntimeError,
                    "Failed to set 'order' in return dictionary");
    goto error_cleanup;
  }
  Py_DECREF(lst);
  cost_obj = PyLong_FromLong(current_cost);
  if (cost_obj == NULL) {
    PyErr_SetString(PyExc_MemoryError,
                    "Failed to create temporary Long Python variable");
    goto error_cleanup;
  }
  if (PyDict_SetItemString(dict, "cost", cost_obj) == -1) {
    PyErr_SetString(PyExc_RuntimeError,
                    "Failed to set 'cost' in return dictionary");
    goto error_cleanup;
  }
  Py_DECREF(cost_obj);

  free(final_arr);

  return dict;

error_cleanup:
  free(final_arr);
  Py_XDECREF(lst);
  Py_XDECREF(cost_obj);
  Py_XDECREF(dict);
  return NULL;
}

static PyMethodDef TSPMethods[] = {
    {"tsp2opt", method_tsp2opt, METH_VARARGS, NULL}, {NULL, NULL, 0, NULL}};

static struct PyModuleDef tspmodule = {PyModuleDef_HEAD_INIT, "tsp",
                                       "TSP 2-opt module", -1, TSPMethods};

PyMODINIT_FUNC PyInit_tsp(void) {
  PyObject *module = PyModule_Create(&tspmodule);
  return module;
}
