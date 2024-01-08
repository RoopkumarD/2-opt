# gcc -c tsp.c -o tsp.o
gcc -c utils.c -o utils.o
# gcc tsp.o utils.o -shared tsp.so
#
# mv ./tsp.so ./venv/lib/python3.10/site-packages/
#
# # removing extra files
# rm *.o
