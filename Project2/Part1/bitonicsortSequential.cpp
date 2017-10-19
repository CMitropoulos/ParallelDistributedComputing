/*
	ECE 566 Parallel and Distributed Computing, Fall 2017
	Programming Project 2. 
*/

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

double randomNum(int upper){
	return (double)rand() / RAND_MAX * upper;
}




int main(int argc, char *argv[]){
	
	//first cl argument specifies tj nb of elements
	const int nbElements  = atoi(argv[1]); 
	double* array = new double[nbElements];

	//generate random numbers to fill the array
	for (int i=0; i< nbElements;i++){
		array[i] = randomNum(100);
	}

    clock_t start, end;
    start=clock();
    bitonicSort(array, 0, nbElements-1);
    end=clock();
	/*
	for (int i=0; i< nbElements;i++){
		cout<< array[i] << endl ;
	}
	*/

	float seconds = ((float)end-(float)start)/ CLOCKS_PER_SEC;
    cout<< "Sequential Bitonicsort time = "<< seconds << " seconds" << endl;
    

    return 0;


}