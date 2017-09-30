#include <iostream>
#include <random>
#include <fstream> 

using namespace std;

int main()
{
    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_real_distribution<> distr(0,8); // define the range
   
    ofstream writeStream; 
    writeStream.open("randomNumbers.txt");	
    for(int i=0; i<20000000; ++i)
        writeStream << distr(eng) << '\n'; // generate numbers and write to file

    writeStream.close();

   return 0;
}
