#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unistd.h>
#include "logic/l_task.hpp"
int main()
{
    const uint16_t numberOfExperimnets = 50;
    const uint16_t numberOfJumps = 100;
    const std::string resultDirName = "Result";
    const std::string inputFileName = "Input";
    
    L_TASK markov_chains(numberOfExperimnets,
        numberOfJumps,
        resultDirName, 
        inputFileName);
    
    markov_chains.readInput();
	std::cout.precision(5);
	//std::cout << std::fixed << std::setprecision(2);
    if (markov_chains.status() == L_TASK::STATUS::OK){
        markov_chains.run();
    }
	
	return 0;
}