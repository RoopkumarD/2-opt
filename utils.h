#ifndef UTILS_H
#define UTILS_H

#include <python3.10/Python.h>

Py_ssize_t get_elem(PyObject *weights, Py_ssize_t row_num, Py_ssize_t col_num);
void hill_climb(int *arr, Py_ssize_t length, PyObject *nodes_weight);
long get_cost(PyObject *weights, int *order, int nodes_length);

#endif // UTILS_H
