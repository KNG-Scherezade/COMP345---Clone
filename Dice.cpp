//! @file 
//! @brief Implementation file for the Dice class  
//!
#include "Dice.h"
#include <string>
#include <vector>
#include <time.h>

//! Static container for diceValues
namespace DiceContainer {
	static std::vector<int> diceValues;
}

//! Implementation of the rolling dice. Error safe.
//! @param string : a string of the form "xdy[+z]".
//! @return an integer which is the addition of the value of all dice and return -1 when the expression dose not follow he right format 
int Dice::roll(std::string diceString)
{
	srand(time(null));

	if (diceString.length() < 3) return -1;
	int returnValue = 0;
	DiceContainer::diceValues.clear();

	int numberOfRolls = 0;
	int typeOfRolls = 0;
	int modifier = 0;
	char operation = 'N';

	int length = diceString.length();
	bool modifierExists = false;

	if (!isdigit(diceString.at(0))) return -1;
	for (int i = 0; i < length; i++){
		if (diceString.at(i) == 'd') {
			numberOfRolls = atoi(diceString.substr(0, i).c_str());
			if (numberOfRolls == 0){
				return -1;
			}
		}
		else if (diceString.at(i) == '+') {
			modifierExists = true;
			int dIndex = diceString.find('d');
			int plusIndex = diceString.find('+');
			int searchLength = plusIndex - dIndex - 1;
			if (dIndex == - 1 || plusIndex == - 1 || searchLength <= 0) {
				return -1;
			}
			typeOfRolls = atoi(diceString.substr(dIndex + 1, searchLength).c_str());
			if (typeOfRolls == 0 || (typeOfRolls != 4 && typeOfRolls != 6 && typeOfRolls != 8 && typeOfRolls != 10 &&
				typeOfRolls != 12 && typeOfRolls != 20 && typeOfRolls != 100)){
				return -1;
			}
			std::string modifierString = diceString.substr(diceString.find('+') + 1);
			int modLength = modifierString.length();
			if (modLength < 1) return -1;
			for (int j = 0; j < modLength; j++) {
				if (!isdigit(modifierString.at(j))) {
					return -1;
				}
			}
			modifier = atoi((modifierString).c_str());
		}
	}
	if (!modifierExists) {
		typeOfRolls = atoi(diceString.substr(diceString.find('d') + 1).c_str());
		if (typeOfRolls == 0 || (typeOfRolls != 4 && typeOfRolls != 6 && typeOfRolls != 8 && typeOfRolls != 10 &&
			typeOfRolls != 12 && typeOfRolls != 20 && typeOfRolls != 100)) {
			return -1;
		}
	}
	for (int i = 0; i < numberOfRolls; i++) {
		int roll  = Dice::randomizeRoll(typeOfRolls);
		DiceContainer::diceValues.push_back(roll);
		returnValue = returnValue + roll;
	}

	for (int i = 0; i < DiceContainer::diceValues.size(); i++) 
		std::cout << DiceContainer::diceValues.at(i) << " ";

	return returnValue + modifier;
}


//! Implementation of the randomizer
//! @param string : a number representing the sides on the die.
//! @return an integer which is the randomization of a roll and return -1000 if error
int Dice::randomizeRoll(int diceType) {
	switch (diceType) {
	case 4: return rand() % 4 + 1;
	case 6: return rand() % 6 + 1;
	case 8: return rand() % 8 + 1;
	case 10: return rand() % 10 + 1;
	case 12: return rand() % 12 + 1;
	case 20: return rand() % 20 + 1;
	case 100: return rand() % 100 + 1;
	default: return -1000;
	}
}

//! Getter function for the namespace DiceContainer and it's vector.
//! @param 
//! @return an integer vector containing dice values.
std::vector<int> Dice::getDiceResults() {
	return DiceContainer::diceValues;
}