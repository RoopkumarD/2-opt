#ifndef UTILS_H
#define UTILS_H

#include <python3.10/Python.h>

Py_ssize_t get_elem(PyObject *weights, Py_ssize_t row_num, Py_ssize_t col_num);

#endif // UTILS_H
