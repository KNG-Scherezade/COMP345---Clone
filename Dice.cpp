#include "Dice.h"
//! Dice class used for rolls
Dice::Dice(void) {
	log = new Logger();
}

//! deconstructor for dice
Dice::~Dice(void) {
	delete log;
}

//! Rolls the given amount of d6 and stores them in an array
int* Dice::roll(int numOfRolls) {
	int* numArray = new int[numOfRolls];
	// create source of randomness, and initialize it with non-deterministic seed
	std::random_device r;
	std::seed_seq seed{ r(),r(),r(),r(),r(),r() };
	std::mt19937 eng{ seed };

	// a distribution that takes randomness and produces values in the range of 1 to 6
	std::uniform_int_distribution<uint32_t> dist(1, 6);

	srand(time(0));
	// Rolls anywhere between 1 and 3 dice.
	for (int i = 0; i < numOfRolls; i++) {
		int roll = dist(eng);
		numArray[i] = roll;
		log->LogDice("D6 rolled: " + std::to_string(roll));
	}

	//Sort the array in descending order
	std::sort(numArray, numArray + numOfRolls, std::greater<int>());

	return numArray;
}

//! Rolls a d10 
//! @return the value rolled between 1 and 10
int Dice::rollD10()
{
	std::random_device r;
	std::seed_seq seed{ r(),r(),r(),r(),r(),r(),r(),r(),r(),r() };
	std::mt19937 randomNum{ seed };
	std::uniform_int_distribution<uint32_t> uint_dist10(1, 10);
	int roll = uint_dist10(randomNum);
	log->LogDice("D10 rolled:  " + std::to_string(roll));
	return roll;
}

//! Rolls a d20 
//! @return the value rolled between 1 and 20
int Dice::rollD20()
{
	std::random_device r;
	std::seed_seq seed{ r(),r(),r(),r(),r(),r(),r(),r(),r(),r(),r(),r(),r(),r(),r(),r(),r(),r(),r(),r() };
	std::mt19937 randomNum{ seed };
	std::uniform_int_distribution<uint32_t> uint_dist10(1, 20);
	int roll = uint_dist10(randomNum);
	log->LogDice("D20 rolled:  " + std::to_string(roll));
	return roll;
}
