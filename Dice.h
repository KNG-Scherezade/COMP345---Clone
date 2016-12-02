#ifndef DICE_HEADER
#define DICE_HEADER

#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <functional>  
#include <random>
#include <iostream>


class Dice {
	private:
		int* ran;
	public:
		int* roll(int numRolls);
		int rollD10();
		Dice(void);
		~Dice(void);
};

#endif