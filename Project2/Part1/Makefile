all : quicksortPthreads quicksortSequential bitonicsortSequential pth_bitonic

quicksortPthreads: quicksortPthreads.cpp
	g++ -std=c++11 -o quicksortPthreads quicksortPthreads.cpp -lpthread

quicksortSequential: quicksortSequential.cpp
	g++ -std=c++11 -o quicksortSequential quicksortSequential.cpp

bitonicsortSequential: bitonicsortSequential.cpp
	g++ -std=c++11 -o bitonicsortSequential bitonicsortSequential.cpp

pth_bitonic: pth_bitonic.c
	gcc -g -Wall -o pth_bitonic pth_bitonic.c -lpthread
