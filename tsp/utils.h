#ifndef UTILS_H
#define UTILS_H

#include <python3.10/Python.h>

Py_ssize_t get_elem(PyObject *weights, Py_ssize_t row_num, Py_ssize_t col_num);
long get_cost(PyObject *weights, int *order, int nodes_length);
void random_walk(int *arr, int nodes_length);
double rand_01(void);
int randrange(int min, int max);

#endif // UTILS_H
