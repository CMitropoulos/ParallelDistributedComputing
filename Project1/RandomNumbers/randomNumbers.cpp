/*
* Create files with random integers.
* The number of integers in each file is a power of 2.
*/

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <random>
#include <fstream> 
#include <cmath>

using namespace std;

int main()
{
  
	ofstream writeStream; 

	for(int i=2; i<30; i+=2){
		string file = to_string(i) ;
		writeStream.open(file+".txt");	
		for(int j=0;j<pow(2,i);j++){
			writeStream << rand() % 1000 + 1 << '\n';
		}
		writeStream.close();
	}
    
   

    

   return 0;
}
