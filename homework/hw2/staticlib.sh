gcc -c vector.c -o vector.o
ar -rc libvector.a vector.o
gcc test.c -o staticvector -L. -lvector