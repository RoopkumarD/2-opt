#include <python3.10/Python.h>

Py_ssize_t get_elem(PyObject *weights, Py_ssize_t row_num, Py_ssize_t col_num) {
  return PyLong_AsSize_t(
      PyList_GetItem(PyList_GetItem(weights, row_num), col_num));
}
