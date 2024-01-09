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
    return NULL;
  }

  srand(time(NULL));
  hill_climb(arr, nodes_length, nodes_weights);

  // building the order
  // +1 for ending the loop
  PyObject *lst = PyList_New(nodes_length + 1);
  if (lst == NULL) {
    puts("Wasn't able to create list");
    return NULL;
  }
  // finding the cost
  int cost = 0;
  for (int i = 0; i < nodes_length - 1; i++) {
    // adding the cost
    cost += get_elem(nodes_weights, arr[i], arr[i + 1]);

    // adding elem in list
    printf("%lu reference of copied\n",
           Py_REFCNT(PyList_GetItem(nodes, arr[i])));
    PyObject *elem = PyUnicode_FromObject(PyList_GetItem(nodes, arr[i]));
    // PyObject *elem = PyUnicode_FromString("hey");
    if (elem == NULL) {
      puts("wasn't able to create elem");
      return NULL;
    }
    printf("%lu reference of elem\n", Py_REFCNT(elem));
    PyList_SetItem(lst, i, elem);
    printf("%lu reference of elem\n", Py_REFCNT(elem));
  }
  cost += get_elem(nodes_weights, arr[nodes_length - 1], arr[0]);
  PyList_SetItem(
      lst, nodes_length - 1,
      PyUnicode_FromObject(PyList_GetItem(nodes, arr[nodes_length - 1])));
  PyList_SetItem(lst, nodes_length,
                 PyUnicode_FromObject(PyList_GetItem(nodes, arr[0])));

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
  if (PyDict_SetItemString(dict, "cost", PyLong_FromLong(cost)) == -1) {
    puts("Failed to assign elem to dict");
    return NULL;
  }

  free(arr);

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
