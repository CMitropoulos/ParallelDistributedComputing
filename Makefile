compile:
	ispc -O2 --arch=x86-64 --target=sse2-i32x4,sse4-i32x8,avx1-i32x16,avx2-i32x16,avx512knl-i32x16,avx512skx-i32x16 square.ispc -o objs/square_ispc.o -h objs/square_ispc.h
	clang++ square.cpp -Iobjs/ -O2 -m64 -c -o objs/square.o
	clang++ -Iobjs/ -O2 -m64 -o square objs/square.o objs/square_ispc.o objs/square_ispc_sse2.o objs/square_ispc_sse4.o objs/square_ispc_avx.o objs/square_ispc_avx2.o objs/square_ispc_avx512knl.o objs/square_ispc_avx512skx.o -lm -lpthread -lstdc++
