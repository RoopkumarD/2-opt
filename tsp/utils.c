#include <python3.10/Python.h>

long get_elem(PyObject *weights, Py_ssize_t row_num, Py_ssize_t col_num) {
  return PyLong_AsLong(
      PyList_GetItem(PyList_GetItem(weights, row_num), col_num));
}

long get_cost(PyObject *weights, int *order, int nodes_length) {
  long cost = 0;
  for (int i = 0; i < nodes_length - 1; i++) {
    cost += get_elem(weights, order[i], order[i + 1]);
  }
  cost += get_elem(weights, order[nodes_length - 1], order[0]);
  return cost;
}

double rand_01(void) { return (double)rand() / (double)RAND_MAX; }

// src https://stackoverflow.com/a/18386648/22554550
int randrange(int min, int max) {
  return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

// src https://stackoverflow.com/a/6852396/22554550
int random_at_most(int max) {
  unsigned long num_bins = (unsigned long)max + 1,
                num_rand = (unsigned long)RAND_MAX + 1,
                bin_size = num_rand / num_bins, defect = num_rand % num_bins;

  long x;
  do {
    x = random();
  } while (num_rand - defect <= (unsigned long)x);

  return x / bin_size;
}

void random_walk(int *arr, int nodes_length) {
  for (int i = 0; i < nodes_length; i++) {
    arr[i] = i;
  }

  for (int i = nodes_length - 1; i > -1; i--) {
    int random_position = random_at_most(i);
    int temp = arr[i];
    arr[i] = arr[random_position];
    arr[random_position] = temp;
  }

  return;
}
