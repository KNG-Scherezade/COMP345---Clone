#include "Dice.h"

Dice::Dice(void) {
}

Dice::~Dice(void) {
}

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
		numArray[i] = dist(eng);
	}

	//Sort the array in descending order
	std::sort(numArray, numArray + numOfRolls, std::greater<int>());
	return numArray;
}

int Dice::rollD10()
{
	std::mt19937 randomNum;
	std::uniform_int_distribution<uint32_t> uint_dist10(1, 10);
	return uint_dist10(randomNum);
}
