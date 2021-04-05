gcc -c main.c
gcc -c stack.c
gcc -c number.c
gcc -c operation.c
gcc main.o stack.o number.o operation.o -lm -o piezon

rm *.o
./piezon
rm piezon