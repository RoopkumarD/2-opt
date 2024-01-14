#ifndef SA_H
#define SA_H

#include <python3.10/Python.h>

void simulated_annealing(int *arr, Py_ssize_t length, PyObject *nodes_weight,
                         int max_iterations, double initial_temp, float alpha);

#endif // SA_H
