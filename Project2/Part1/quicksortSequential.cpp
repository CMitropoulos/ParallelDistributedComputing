/*
	ECE 566 Parallel and Distributed Computing, Fall 2017
	Programming Project 2. 
*/


#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <random>
using namespace std;

double* fillArray(double* array, int nbElements){
  //generate random numbers to fill the array
  int upper =100; //max number allowed
  random_device rd; // obtain a random number from hardware
  mt19937 eng(rd()); // seed the generator
  uniform_real_distribution<> distr(0,100); 
  for (int i=0; i< nbElements;i++){
    array[i] = distr(eng);
  }
  return array;
}

void quickSort(double arr[], int left, int right) {
      int i = left, j = right;
      double tmp;
      double pivot = arr[(left + right) / 2];
 
      /* partition */
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };
 
      /* recursion */
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}


int main(int argc, char *argv[]){
	
	//first cl argument specifies tj nb of elements
	const int nbElements  = atoi(argv[1]); 
	double* array = new double[nbElements];

	array = fillArray(array, nbElements);

    clock_t start, end;
    start=clock();
    quickSort(array, 0, nbElements-1);
    end=clock();
	/*
	for (int i=0; i< nbElements;i++){
		cout<< array[i] << endl ;
	}
	*/

	float seconds = ((float)end-(float)start)/ CLOCKS_PER_SEC;
    cout<< "Sequential Quicksort time = "<< seconds << " seconds" << endl;
    

    return 0;


}