default:
	ispc -O2 --arch=x86-64 --target=sse2 proj1.ispc -o ispc.o -h proj1ispc.h
	clang -m64 -Iobjs/ -O3 -Wall -c -o proj1ispc.o proj1ispc.c
	clang++ -m64 -Iobjs/ -O3 -Wall -c -o tasksys.o tasksys.cpp
	clang++ -m64 -Iobjs/ -O3 -Wall -o randispc proj1ispc.o ispc.o tasksys.o -lpthread
avx:
	clang++ -m64 -Iobjs/ -O2 -Wall  -mavx -o randavx proj1avx.cpp   tasksys.o -lpthread
