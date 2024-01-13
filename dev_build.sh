gcc -c ./tsp/tspmodule.c -o tsp.o -fPIC
gcc -c ./tsp/utils.c -o utils.o -fPIC
gcc -c ./tsp/hill_climb.c -o hill_climb.o -fPIC
gcc -c ./tsp/simulated_annealing.c -lm -o simulated_annealing.o -fPIC
gcc tsp.o utils.o hill_climb.o simulated_annealing.o -shared -o tspsolver.so

mv ./tspsolver.so ./venv/lib/python3.10/site-packages/

# removing extra files
rm *.o
