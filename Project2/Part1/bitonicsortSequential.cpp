/* C++ Program for Bitonic Sort. 
  ECE 566 Parallel and Distributed Computing, Fall 2017
  Programming Project 2.

 */



#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <random>
using namespace std;


int* fillArray(int* array, int nbElements) {
	//generate random numbers to fill the array
	int upper = 100; //max number allowed
	random_device rd; // obtain a random number from hardware
	mt19937 eng(rd()); // seed the generator
	uniform_int_distribution<int> distribution(0, 100);
	for (int i = 0; i < nbElements; i++) {
		array[i] = distribution(eng);
	}
	return array;
}


/*The parameter dir indicates the sorting direction, ASCENDING
   or DESCENDING; if (a[i] > a[j]) agrees with the direction,
   then a[i] and a[j] are interchanged.*/
void compAndSwap(int a[], int i, int j, int dir)
{
	if (dir == (a[i] > a[j]))
		swap(a[i], a[j]);
}

/*It recursively sorts a bitonic sequence in ascending order,
  if dir = 1, and in descending order otherwise (means dir=0).
  The sequence to be sorted starts at index position low,
  the parameter cnt is the number of elements to be sorted.*/
void bitonicMerge(int a[], int low, int cnt, int dir)
{
	if (cnt > 1)
	{
		int k = cnt / 2;
		for (int i = low; i < low + k; i++)
			compAndSwap(a, i, i + k, dir);
		bitonicMerge(a, low, k, dir);
		bitonicMerge(a, low + k, k, dir);
	}
}

/* This function first produces a bitonic sequence by recursively
    sorting its two halves in opposite sorting orders, and then
    calls bitonicMerge to make them in the same order */
void bitonicSort(int a[], int low, int cnt, int dir)
{
	if (cnt > 1)
	{
		int k = cnt / 2;

		// sort in ascending order since dir here is 1
		bitonicSort(a, low, k, 1);

		// sort in descending order since dir here is 0
		bitonicSort(a, low + k, k, 0);

		// Will merge wole sequence in ascending order
		// since dir=1.
		bitonicMerge(a, low, cnt, dir);
	}
}

/* Caller of bitonicSort for sorting the entire array of
   length N in ASCENDING order */
void sort(int a[], int N, int up)
{
	bitonicSort(a, 0, N, up);
}

// Driver code
int main(int argc, char *argv[]) {

	int nbElements = atoi(argv[1]);
	int* a = new int[nbElements];

	a = fillArray(a, nbElements);
	
	int up = 1;   // means sort in ascending order

	clock_t start, end;
	start = clock();

	sort(a, nbElements, up);

	end = clock();

	/*printf("Sorted array: \n");
	for (int i = 0; i < nbElements; i++)
		cout << a[i] << endl;
*/
	float seconds = ((float)end - (float)start) / CLOCKS_PER_SEC;
	cout << "Sequential Bitonicsort time = " << seconds << " seconds" << endl;


	return 0;
}