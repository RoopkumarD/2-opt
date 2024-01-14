import os

from setuptools import Extension, find_packages, setup

setup(
    ext_modules=[
        Extension(
            name="tspsolver",
            sources=[
                "tsp/tspmodule.c",
                "tsp/utils.c",
                "tsp/hill_climb.c",
                "tsp/simulated_annealing.c",
            ],
            include_dirs=[os.path.dirname(os.path.realpath(__file__))],
        ),
    ],
    packages=find_packages(exclude=["tests"]),
    include_package_data=True,
)
