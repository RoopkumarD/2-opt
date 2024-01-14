#include "utils.h"
#include <math.h>
#include <python3.10/Python.h>

void simulated_annealing(int *arr, Py_ssize_t length, PyObject *nodes_weight,
                         int max_iterations, double initial_temp, float alpha) {
  const double temp = initial_temp;

  // initial start
  random_walk(arr, length);
  for (int i = 0; i < max_iterations; i++) {
    double current_temp = temp * exp(-(alpha * i));

    // choose a random neighbour based on 2-opt
    int start_elem = randrange(0, length - 3);
    int end_elem_max = length - 1;

    if ((start_elem + 1 + (length - 3)) < length - 1) {
      end_elem_max = start_elem + 1 + (length - 3);
    }
    int end_elem = randrange(start_elem + 2, end_elem_max);

    // calculate the delta_cost based on how good it is
    int start_other = (start_elem + 1) % length;
    int end_other = (end_elem + 1) % length;

    int delta_cost = get_elem(nodes_weight, arr[start_elem], arr[start_other]) +
                     get_elem(nodes_weight, arr[end_elem], arr[end_other]) -
                     get_elem(nodes_weight, arr[start_elem], arr[end_elem]) -
                     get_elem(nodes_weight, arr[start_other], arr[end_other]);

    int update = 0;
    // if it is good delta > 0, then accept
    if (delta_cost > 0) {
      update = 1;
    }
    // else calculate the probability by e...
    else {
      // probability
      double p = exp((double)delta_cost / current_temp);
      // Then generate a random number between 0 to 1
      double random_real_num = rand_01();
      if (random_real_num <= p) {
        update = 1;
      }
    }

    if (update == 1) {
      start_elem += 1;
      int width = end_elem - start_elem;
      int above_mid_point = 0;

      if (width % 2 == 0) {
        above_mid_point = start_elem + (int)(width / 2);
      } else {
        above_mid_point = end_elem - (int)(width / 2);
      }

      for (int m = start_elem; m < above_mid_point; m++) {
        int temp = arr[end_elem - (m - start_elem)];
        arr[end_elem - (m - start_elem)] = arr[m];
        arr[m] = temp;
      }
    }
  }

  return;
}
