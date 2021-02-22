gcc -fpic -shared vector.c -o libvector.so 
gcc test.c -o dynamicvector -L. ./libvector.so