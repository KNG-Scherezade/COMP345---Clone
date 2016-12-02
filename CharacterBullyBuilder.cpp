//!	 @file CharacterBullyBuilder.cpp
//!  @brief Concrete builder implementation of the bully fighter
//!
//!  This class builds a bully fighter which has stats tailored for dealing damage
//!  Hitpoints, attack bonus and number of attacks are also set based on the level of the fighter.
//!  The d20 rules followed are: (1) his hit points go up by(1d10 + constitution modifier), 
//!  (2) his attack bonus goes up by one, (3) His number of attacks go up by 1 every 5 levels
//!	 A bully's score is attributed according to Strength, Constitution, Dexterity, Intelligence, Charisma, Wisdom
//!  in that order.
#include "CharacterBullyBuilder.h"
#include "Dice.h"
#include <vector>
#include <algorithm>
#include "Fighter.h"
#include "Logger.h"

CharacterBullyBuilder::CharacterBullyBuilder()
{
}


CharacterBullyBuilder::~CharacterBullyBuilder()
{
}

//! Builds a bully character that is built for dealing damage
//! @param level: the level of the character
void CharacterBullyBuilder::buildCharacter(int level)
{
	log = Logger();
	// Ability score generation
	Dice dice = Dice();

	
	vector<int> scores = vector<int>(6);

	// For all 6 ability scores
	for (int i = 0; i < 6; i++)
	{
		// rolls 4 d6 and stores the result in an array in descending order
		int* rolls = dice.roll(4);
		// log all 4 dice rolls for the ability score at the given iteration
		log.LogDice("ability score " + to_string(i) + " d6 roll 1 value: " + to_string(rolls[0]));
		log.LogDice("ability score " + to_string(i) + " d6 roll 2 value: " + to_string(rolls[1]));
		log.LogDice("ability score " + to_string(i) + " d6 roll 3 value: " + to_string(rolls[2]));
		log.LogDice("ability score " + to_string(i) + " d6 roll 4 value: " + to_string(rolls[3]));
		// Score is equal to the sum of the three highest d6 rolls		
		scores[i] = rolls[0] + rolls[1] + rolls[2];
		log.LogDice("ability score stored using the 3 highest rolls: " + to_string(scores[i]));
	}

	// Sort scores in descending order
	std::sort(scores.begin(), scores.end(), std::greater<int>());

	log.LogCharacter("Setting bully character ability scores");
	// Set stats according to order of importance
	log.LogCharacter("Setting character strength: " + to_string(scores[0]));
	c_character->setStr(scores[0]);
	log.LogCharacter("Setting character consitution: " + to_string(scores[1]));
	c_character->setCon(scores[1]);
	log.LogCharacter("Setting character dexterity: " + to_string(scores[2]));
	c_character->setDex(scores[2]);
	log.LogCharacter("Setting character intelligence: " + to_string(scores[3]));
	c_character->setIntel(scores[3]);
	log.LogCharacter("Setting character charisma: " + to_string(scores[4]));
	c_character->setCha(scores[4]);
	log.LogCharacter("Setting character wisdom: " + to_string(scores[5]));
	c_character->setWis(scores[5]);

	// Sets modifiers, armor class, damage bonus
	c_character->createClass();

	// Level-dependent characteristics
	c_character->setLevel(level);

	// Set hp
	int hp = 0;
	// HP increases by 1d10 + con modifier per level
	for (int i = 0; i < level; i++)
	{
		int roll = dice.rollD10();
		log.LogDice("hp roll d10 value: " + to_string(roll));
		hp += roll + c_character->getCon_mod();
	}

	c_character->setHp(hp);
	c_character->setMaxHp(hp);

	// Set attack bonus
	int atkBonus = c_character->getAttackBonus();
	// Attack bonus goes up by 1 per level
	atkBonus += level;
	c_character->setAttackBonus(atkBonus);

	// Set attacks per round. Starting at 1 attack and gaining another every 5 levels.
	// Example character is level 5: 5 -1 = 4,	4/5 = 0, 0 + 1 = 1 attack.
	c_character->setNumAtks((level - 1) / 5 + 1);

}

