#include <python3.10/Python.h>

Py_ssize_t get_elem(PyObject *weights, Py_ssize_t row_num, Py_ssize_t col_num) {
  return PyLong_AsSize_t(
      PyList_GetItem(PyList_GetItem(weights, row_num), col_num));
}

void random_walk(int nodes_length) {
  // since we know the config will always be [0,1,2,3,...,n]
  int path[nodes_length];
  for (int i = nodes_length - 1; i > -1; i--) {
    printf("%i\n", i);
  }

  return;
}
