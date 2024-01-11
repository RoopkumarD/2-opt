gcc -c ./tsp/tspmodule.c -o tsp.o -fPIC
gcc -c ./tsp/utils.c -o utils.o -fPIC
gcc tsp.o utils.o -shared -o tsp.so

mv ./tsp.so ./venv/lib/python3.10/site-packages/

# removing extra files
rm *.o