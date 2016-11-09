//! @file A1_40012407_DiceRollExample
//! @brief Header file for the Dice class  
/*! Game Rules:
	Dice in the d20 ruleset are described in terms of the expression "xdy+z" implying the number of dice(x) rolled of a certain type(y) plus an optional modifier.
	In scenarios requiring the user to roll a dice they may chose between the d4,d6,d8,d10,d12,d20 or d100.
	In the case physically playing the game the d100 involves two rolls of the d10 using the first roll as the 1s and the second roll as the 10s where two 10s make 100 and two 1s make 11.
	In the digital game this can just be done through RNG.
	
	Rolls are done whenever an action which could fail needs to be decided.
	Depending on the action different type of dice will be rolled.
	Character creation uses d6 while combat uses the d20.
	
	Dice rolls in d20 also have modifiers that can act to alter the value of the xdy dice roll by increasing the total roll of the dice.
	Modifiers an come from stats such as the armor bonus, or a dodge bonus. In other scenarios.
	
	The most significant of roles is the attack roll where you roll a d20 die and check if it comes up on a 1 or 20.
	If it comes up with a 1 you miss, and if it comes up with a 20 it's an automatice hit.
	You then add a modifier and if the combined value of 1d20+AB surpasses the enemies armor class, you land a hit.

	In this implementation of the dice roll, it takes a string expression of xdy with the optional +z and returns a value.
	Each dice roll is stored in a vector in case there are scenarios where the dice rolls may need to be known such as during the d20 attack roll for miss and absolute hits.
	
*/
/*! Design Considerations:
	This design makes use of static variables in a dice class.
	A public static roll function returns an int when it is called.
	If the string that is inputted into the roll function is valid(meets the criterea of xdy or xdy+z) it returns the result while if it is invalid it returns -1.
	If the rolls are valid it goes through a private static function which is a randomizer returning the result of a single dice.
	This private randomizer takes a type of dice and is called itterativly in the public static roll function.
	
	The static nature of the method means that it can be called anywhere, which is ideal for a dice function which does not neccicarily require stored variables
*/
/*! Libraries:
	CPPUnit: This is a good library for doing quick tests on your fuctions and determining their validity.
	SDL2: A low level library for handling GUI creation utilizing an OpenGL wrapper. It gives control over use of GPU or CPU and is a good library to use as a precursor to OpenGL.
	SDL_TTF: Allows one to create text easily using TTF files.
	SDL_Image: A library that makes image loading easier for SDL through implementing png and jpg loading.
*/
#pragma once

#include <iostream>
#include <vector>
//! class that implements the rolling of Dice 
class Dice
{
public:
	static int roll(std::string string);
	static std::vector<int> getDiceResults();
private:
	static int randomizeRoll(int diceType);
};