#include "utils.h"

static PyObject *method_tsp(PyObject *self, PyObject *args) {
  PyObject *nodes_weights;
  int repeat = 1;

  if (!PyArg_ParseTuple(args, "O|i", &nodes_weights, &repeat)) {
    return NULL;
  }

  Py_ssize_t nodes_length = PyList_Size(nodes_weights);
  srand(time(NULL));

  int *final_arr = NULL;
  int current_delta_cost = 0;

  for (int i = 0; i < repeat; i++) {
    int *arr = (int *)malloc(nodes_length * sizeof(int));
    if (arr == NULL) {
      puts("Wasn't able to allocate memory");
      return NULL;
    }

    int delta_cost = hill_climb(arr, nodes_length, nodes_weights);
    // mistake!!!!!!
    // can't compare two different starting arr delta_cost
    if (delta_cost < current_delta_cost) {
      if (final_arr != NULL) {
        free(final_arr);
      }
      current_delta_cost = delta_cost;
      final_arr = arr;
    } else {
      free(arr);
    }
  }

  // building the order
  PyObject *lst = PyList_New(nodes_length);
  if (lst == NULL) {
    puts("Wasn't able to create list");
    return NULL;
  }
  // finding the cost
  int cost = 0;
  for (int i = 0; i < nodes_length - 1; i++) {
    // adding the cost
    cost += get_elem(nodes_weights, final_arr[i], final_arr[i + 1]);

    // adding elem in list
    PyObject *elem = PyLong_FromLong(final_arr[i]);
    if (elem == NULL) {
      puts("Wasn't able to copy");
      return NULL;
    }
    PyList_SetItem(lst, i, elem);
  }
  // for last elem
  cost += get_elem(nodes_weights, final_arr[nodes_length - 1], final_arr[0]);
  PyObject *elem = PyLong_FromLong(final_arr[nodes_length - 1]);
  if (elem == NULL) {
    puts("Wasn't able to copy");
    return NULL;
  }
  PyList_SetItem(lst, nodes_length - 1, elem);

  // combining results in dict
  PyObject *dict = PyDict_New();
  if (dict == NULL) {
    puts("Wasn't able to create list");
    return NULL;
  }
  if (PyDict_SetItemString(dict, "order", lst) == -1) {
    puts("Failed to assign elem to dict");
    return NULL;
  }
  Py_DECREF(lst);
  PyObject *cost_obj = PyLong_FromLong(cost);
  if (cost_obj == NULL) {
    puts("cost obj null");
    return NULL;
  }
  if (PyDict_SetItemString(dict, "cost", cost_obj) == -1) {
    puts("Failed to assign elem to dict");
    return NULL;
  }
  Py_DECREF(cost_obj);

  free(final_arr);

  return dict;
}

static PyMethodDef TSPMethods[] = {{"tsp", method_tsp, METH_VARARGS, NULL},
                                   {NULL, NULL, 0, NULL}};

static struct PyModuleDef tspmodule = {PyModuleDef_HEAD_INIT, "tsp",
                                       "TSP module", -1, TSPMethods};

PyMODINIT_FUNC PyInit_tsp(void) {
  PyObject *module = PyModule_Create(&tspmodule);
  return module;
}
