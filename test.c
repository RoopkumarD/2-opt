#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// src https://stackoverflow.com/a/6852396/22554550
// Assumes 0 <= max <= RAND_MAX
// Returns in the closed interval [0, max]
int random_at_most(int max) {
  unsigned long
      // max <= RAND_MAX < ULONG_MAX, so this is okay.
      num_bins = (unsigned long)max + 1,
      num_rand = (unsigned long)RAND_MAX + 1, bin_size = num_rand / num_bins,
      defect = num_rand % num_bins;

  long x;
  do {
    x = random();
  }
  // This is carefully written not to overflow
  while (num_rand - defect <= (unsigned long)x);

  // Truncated division is intentional
  return x / bin_size;
}

void random_walk(int nodes_length) {
  // since we know the config will always be [0,1,2,3,...,n]
  int path[nodes_length];
  for (int i = 0; i < nodes_length; i++) {
    path[i] = i;
  }

  for (int i = nodes_length - 1; i > -1; i--) {
    int random_position = random_at_most(i);
    int temp = path[i];
    path[i] = path[random_position];
    path[random_position] = temp;
  }

  for (int i = 0; i < nodes_length; i++) {
    printf("%i\n", path[i]);
  }

  return;
}

int main(void) {
  srand(time(NULL));
  random_walk(4);
  return 0;
}
