default:
	ispc -O2 --arch=x86-64 --target=sse2 proj1.ispc -o ispc.o -h proj1ispc.h
	gcc -m64 -Iobjs/ -O3 -Wall -c -o proj1ispc.o proj1ispc.c
	g++ -m64 -Iobjs/ -O3 -Wall -o randispc proj1ispc.o ispc.o tasksys.o
avx:
	g++ -m64 -Iobjs/ -O2 -Wall  -mavx -o randavx proj1avx.cpp   tasksys.o