compile:
	ispc -O2 --arch=x86-64 --target=sse2-i32x4,sse4-i32x8,avx1-i32x16,avx2-i32x16,avx512knl-i32x16,avx512skx-i32x16 square_tasks.ispc -o objs/square_tasks_ispc.o -h objs/square_tasks_ispc.h
	clang++ square_tasks.cpp -Iobjs/ -O2 -m64 -c -o objs/square_tasks.o
	clang++ -Iobjs/ -O2 -m64 -o square_tasks objs/square_tasks.o objs/square_tasks_ispc.o objs/square_tasks_ispc_sse2.o objs/square_tasks_ispc_sse4.o objs/square_tasks_ispc_avx.o objs/square_tasks_ispc_avx2.o objs/square_tasks_ispc_avx512knl.o objs/square_tasks_ispc_avx512skx.o -lm -lpthread -lstdc++

