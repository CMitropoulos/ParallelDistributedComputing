/**
 *
 * ECE 566 Parallel and Distributed Computing, Fall 2017
 * Final Project
 * Sequential Version of Quicksort - Random Pivot Selection
 *
 * Author: Christos Mitropoulos 
 * Email: chris.mitropoulos@gmail.com
 *
 * */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include <vector>
#include <iostream>
#include <random>

std::vector<int> readFiletoVector(const std::string& filename){
	std::ifstream source;
	source.open(filename.c_str());
	std::vector<int> array;
	int number;

	while(source>>number){
		array.push_back(number);
	}
	return array;

}

void displayVector(const std::vector<int> v)
{
	    for (int i(0); i <= v.size(); ++i)
		            std::cout << "\n" << v[i];
}

int partition(std::vector<int>&v, int low, int high){
	int pivot = v[high];
	int i = (low -1);
	int temp = 0;
	for(int j = low; j<=high-1; j++){
		if(v[j]<=pivot){
			i++;
			std::swap(v[i],v[j]);
		}
	}
	std::swap(v[i+1],v[high]);
	return i+1;
}

void quickSort(std::vector<int> &v, int low, int high){
	if(low<high){
	//pivot is partitioning index v[pivot] is in the correct place
	int pivot = partition(v, low, high);
	//Separetaly sort before the partition
	//and after the partition
	quickSort(v, low, pivot - 1);
	quickSort(v, pivot, high);

	}

}

int main(int argc, char *argv[]){

	std::string numbersFilename(argv[1]);

	//read array from 1st cli argument
	std::vector<int> input = readFiletoVector(numbersFilename);
	quickSort(input,0,input.size()-1);
	//displayVector(input);
	




	return 0;

}
