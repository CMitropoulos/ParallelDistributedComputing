/*
	ECE 566 Parallel and Distributed Computing, Fall 2017
	Programming Project 1. 
*/

#include <iostream>
#include <stdio.h>
#include <cmath>
#include "square_tasks_ispc.h"
#include <stdlib.h>
#include "timing.h"

using namespace std;
using namespace ispc;


double randomNum(int upper){
	return (double)rand() / RAND_MAX * upper;
}

double calRoot(double input, double firstGuess){
	double x1 = -1.0;
    double x0 = -1.0;

    x0 = firstGuess;
    do{
        x1 = (x0 - (((x0 * x0) - input) / (2 * x0)));
        x0 = x1;
    }while((x1 * x1) - input > 1e-4);

    return x1;
}

void calRoot_serial(double times, float* values, float* result, float firstGuess){

	for(int i = 0; i < times; i ++){
		result[i] = calRoot(values[i], firstGuess);
	}
}

int main(int argc, char *argv[]){

const unsigned int totalNum = 20 * 1e6;
	const float firstGuess = 2.0f;
	double minISPC = 1e30;
	float* values = new float[totalNum];
	float* result = new float[totalNum];
	// generate N float num;
	for(int i = 0; i < totalNum; i++){
		values[i] = randomNum(8);
		result[i] = 0.0;
	}

	

	for(unsigned int i = 0; i < 3; i++){
		reset_and_start_timer();
		calRoot_ispc(totalNum, values, result, firstGuess);
		double dt = get_elapsed_mcycles();
    		printf("@time of ISPC run:\t\t\t[%.3f] million cycles\n", dt);
	        minISPC = std::min(minISPC, dt); 
	}
      	printf("[root calculate ISPC]:\t\t[%.3f] million cycles\n", minISPC);

	double minSerial = 1e30;
	for(unsigned int i = 0 ; i < 3; i ++){
		reset_and_start_timer();
		calRoot_serial(totalNum, values, result, firstGuess);
		double dt = get_elapsed_mcycles();
    		printf("@time of serial run:\t\t\t[%.3f] million cycles\n", dt);
        	minSerial = std::min(minSerial, dt); 
	}
    	printf("[root calculate serial]:\t\t[%.3f] million cycles\n", minSerial);

    	printf("\t\t\t\t(%.2fx speedup from ISPC)\n", minSerial/minISPC);

    	delete[] values;
    	delete[] result;
	return 0;
}




