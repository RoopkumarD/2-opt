[![license](https://img.shields.io/badge/license-MIT-success)](https://github.com/RoopkumarD/tspsolver/blob/main/LICENSE.md)

# TSP Solver with Optimization Strategies

This Python library, implemented in C, offers an efficient approximate solution for the Travelling Salesman Problem (TSP). It
leverages the 2-opt heuristic and simulated annealing approach to find optimal routes.

## Get Started

This library has no dependencies and can be used by building a wheel (whl) file.

First, let's download `build`, which will help us build this library:

```bash
pip install build
```

Then run this command:

```bash
python -m build
```

This will generate a `dist` directory containing our library's wheel (whl) file.

Now, you can either install the library globally, but I would recommend creating a virtual environment:

```bash
python3 -m venv venv
source venv/bin/activate
```

Now let's install the library.

```bash
pip install dist/tsp-...whl
```

## Usage

This library provides two methods to solve TSP problems: one employs a classic hill climb with random restart, and the other
uses a simulated annealing approach. Both methods utilize the 2-opt heuristic to find the nearest neighbor.

To use this module, you need a distance matrix `dist_mat` representing the pairwise distances between all nodes. Here,
`dist_mat[i][j]` denotes the distance from node i to node j.

```python
cost = [
    [0, 2451, ...,1420, 2145, 1972],
    ...
    [1972, 579, ..., 1200, 504, 0],
]
```

### Classic Hill Climb with Random Restart

```python
from tspsolver import tsp2opt

# The first argument is dist_mat,
# and the second argument is the number of random restart iterations.
k = tsp2opt(cost, 4)
print(k)
```

This will output:

```bash
{'order': [7, 0, 9, 5, 10, 11, 1, 8, 6, 12, 4, 3, 2], 'cost': 7293}
```

Here, 'order' represents the sequence to follow, and it is cyclic. The 'cost' is the total distance traveled for this
sequence.

### Simulated Annealing

```python
from tspsolver import tspsa

# The first argument is the cost matrix,
# the second argument is the number of iterations for simulated annealing,
# the third argument is the initial temperature,
# and the fourth argument is the cooling factor (alpha)

result = tspsa(cost, 500, 1000, 0.03)
print(result)
```

This will yield the same result as the classic hill climb with random restart.

For cooling scheduling, the simulated annealing uses an exponential function

```c
double current_temp = temp * exp(-(alpha * i));
```

## Issues and Support

If you encounter any issues or have questions about using the library, please feel free to [open an
issue](https://github.com/RoopkumarD/tspsolver/issues) on the GitHub repository. Your feedback and contributions are welcome!

## References

This library was developed with the help of the following resources:

- [Solving header files issue](https://stackoverflow.com/questions/76467019/solved-how-to-get-cffi-and-setuptools-to-find-c-files-and-headers)
- [Used py2opt lib readme as base for this readme](https://github.com/pdrm83/py2opt)
- [C extension learning](https://llllllllll.github.io/c-extension-tutorial/index.html)
- [C extension learning](https://pythonextensionpatterns.readthedocs.io/en/latest/refcount.html#)
- [Original Python docs for C API](https://docs.python.org/3/c-api/)
- [Example inspiration](https://developers.google.com/optimization/routing/tsp#complete_programs)
- [Packaging the extension](https://setuptools.pypa.io/en/latest/userguide/ext_modules.html)
- [Guide for publishing the library](https://packaging.python.org/en/latest/tutorials/packaging-projects/)
