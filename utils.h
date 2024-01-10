#ifndef UTILS_H
#define UTILS_H

#include <python3.10/Python.h>

Py_ssize_t get_elem(PyObject *weights, Py_ssize_t row_num, Py_ssize_t col_num);
int hill_climb(int *arr, Py_ssize_t length, PyObject *nodes_weight);

#endif // UTILS_H
