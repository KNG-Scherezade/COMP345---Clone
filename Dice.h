#ifndef DICE_HEADER
#define DICE_HEADER

#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <functional>  
#include <random>
#include <iostream>
#include "Logger.h"
class Dice {
	private:
		int* ran;
		Logger* log;
	public:
		int* roll(int numRolls);
		int rollD10();
		int rollD20();
		Dice(void);
		~Dice(void);
};

#endif