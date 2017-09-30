#include <iostream>
#include <random>
int main()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_real_distribution<> distr(0,8); // define the range

    for(int i=0; i<10; ++i)
        std::cout << distr(eng) << '\n'; // generate numbers
}
