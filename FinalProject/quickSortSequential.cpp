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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <random>
#include <string.h>

std::vector<int> readFiletoVector(const std::string& filename) {
	std::ifstream source;
	source.open(filename.c_str());
	std::vector<int> array;
	int number;

	while (source >> number) {
		array.push_back(number);
	}
	return array;

}

void displayVector(const std::vector<int> v)
{
	for (int i(0); i <= v.size(); ++i)
		std::cout << "\n" << v[i];
}

void writeVectortoFile(const std::vector<int> v, std::string filename) {
	std::ofstream out(filename);
	std::cout << "Start writing solutions \n" ;
	for (int i(0); i < v.size(); ++i) {
		out << std::to_string(v[i]) << "\n";
	}
	std::cout << "Finished writing solutions at " << filename << std::endl;

	out.close();
}

int partition(std::vector<int>&v, int low, int high) {
	int pivot = v[high];
	int i = (low - 1);
	int temp = 0;
	for (int j = low; j <= high - 1; j++) {
		if (v[j] <= pivot) {
			i++;
			std::swap(v[i], v[j]);
		}
	}
	std::swap(v[i + 1], v[high]);
	return i + 1;
}

void quickSort(std::vector<int> &v, int low, int high) {
	if (low < high) {
		//pivot is partitioning index v[pivot] is in the correct place
		int pivot = partition(v, low, high);
		//Separetaly sort before the partition
		//and after the partition
		quickSort(v, low, pivot - 1);
		quickSort(v, pivot, high);

	}

}

int main(int argc, char *argv[]) {

	std::string numbersFilename(argv[1]);

	//read array from 1st cli argument
	std::vector<int> v = readFiletoVector(numbersFilename);
	quickSort(v, 0, v.size() - 1);
	//displayVector(v);

	//write solutions to file
	if ( (argc >= 3 ) && (strcmp(argv[2], "write_solutions") == 0) ) {
		writeVectortoFile(v, "solutions/" + numbersFilename);
	}

	//test solutions
	if ( (argc >= 3 ) && (strcmp(argv[2], "test_solutions") == 0) ) {
		std::vector<int> solutions = readFiletoVector("solutions/" + numbersFilename);
		v == solutions ? std::cout << "Correct\n" : std::cout << "False\n" ;
	}


	return 0;

}
