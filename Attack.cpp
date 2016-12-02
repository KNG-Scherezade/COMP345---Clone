#include "Attack.h"

#include "Dice.h"
#include "GenericMapItem.h"
#include "character.h"
#include "Monster.h"

//!When you make an attack, your attack roll determines whether the attack hits or misses. 
//!To make an attack roll, roll a d20 and add the appropriate modifiers. 
//!If the total of the roll plus modifiers equals or exceeds the targetfs Armor Class (AC), the attack hits.
//!The AC of a character is determined at character creation, whereas the AC of a monster is in its stat block.

Attack::Attack()
{
}


Attack::~Attack()
{
}


std::string Attack::makeAttack(Character* chara, Monster* mons) {
	Dice dice;
	int roll = dice.rollD20();
	int dmg = 0;
	std::string rtnString = "\n\n";
	Logger log;
	if (roll == 20) {
		crit = true;
		rtnString += "You rolled a " + std::to_string(roll) + ". You Crit(2x damage).";
		log.LogCharacter("Player rolled a 20 for a crit");
	}
	else if (roll == 1) {
		miss = true;
		log.LogCharacter("Player rolled a 1 and missed");
		return "You rolled a " + std::to_string(roll) + ". You Missed.";
	}
	else {
		rtnString += "You rolled a " + std::to_string(roll);
		miss = calculateHit(chara, mons, roll);
	}

	if (miss) {
		rtnString += ". You Missed." + std::to_string(roll) + " + " + std::to_string(chara->getAttackBonus()) + " < " + std::to_string(chara->getAc());
		log.LogCharacter(std::to_string(roll) + " + " + std::to_string(mons->calculateBaseAttackBonus()) + " < " + std::to_string(chara->getAc()) + " MISS");
	}
	else {
		rtnString += ". You Hit.";
		log.LogCharacter(std::to_string(roll) + " + " + std::to_string(mons->calculateBaseAttackBonus()) + " > " + std::to_string(chara->getAc()) + " HIT");
		if (chara->getWeapon() == NULL) {
			dmg = chara->getStr_mod() + 1;
		}
		else {
			dmg = chara->getWeapon()->getDamage() + chara->getDamageBonus();
		}
	}
	if (crit) {
		dmg *= 2;
		log.LogCharacter("Crit doubled damage to " + dmg);
		crit = false;
	}
	if (dmg > 0)
		mons->setCurrentHP(mons->getCurrentHP() - dmg);
	else {
		mons->setCurrentHP(mons->getCurrentHP());
		log.LogCharacter("Player damaged Monster by " + dmg);
	}

	return rtnString;
}

std::string Attack::makeAttack(Monster* mons, Character* chara) {
	Dice dice;
	int roll = dice.rollD20();
	int dmg = 0;
	std::string rtnString;
	Logger log;
	if (roll == 20) {
		crit = true;
		rtnString += "It rolled a " + std::to_string(roll) + ". It Crits(2x damage).";
		log.LogCharacter("Monster rolled a 20 for a crit");
	}
	else if (roll == 1) {
		miss = true;
		log.LogCharacter("Monster rolled a 1 and missed");
		return "It rolled a " + std::to_string(roll) + ". It Missed.";

	}
	else {
		rtnString += "It rolled a " + std::to_string(roll);
		miss = calculateHit(mons, chara, roll);
	}

	if (miss) {
		rtnString += ". It Missed. " + std::to_string(roll) + " + " + std::to_string(mons->calculateBaseAttackBonus()) + " < " + std::to_string(chara->getAc());
		log.LogCharacter(std::to_string(roll) + " + " + std::to_string(mons->calculateBaseAttackBonus()) + " < " + std::to_string(chara->getAc())+" MISS");
	}
	else {
		rtnString += ". It Hit.";
		dmg = mons->getModifier(mons->getStrength()) + 1;
		log.LogCharacter(std::to_string(roll) + " + " + std::to_string(mons->calculateBaseAttackBonus()) + " > " + std::to_string(chara->getAc()) + " HIT");
	}
	if (crit) {
		dmg *= 2;
		log.LogCharacter("Crit doubled damage to " + dmg);
		crit = false;
	}
	if(dmg > 0)
		chara->hit(dmg);
	else
		chara->hit(0);
	log.LogCharacter("Monster damaged player by " + dmg);
	return rtnString;
	
}

bool Attack::calculateHit(Character* chara, Monster* mons, int roll) {
	Logger log;
	int attack = roll + chara->getAttackBonus();
	int armourClass = mons->ac;
	log.LogCharacter("Player attack of " + to_string(attack) + "was compared against Monster armour of" + to_string(mons->ac));
	return armourClass > attack;
}

bool Attack::calculateHit(Monster* mons, Character* chara, int roll) {
	Logger log;
	int attack = roll + (mons)->calculateBaseAttackBonus();
	int armourClass = chara->getAc();
	log.LogCharacter("Monster attack of " + to_string(attack) + "was compared against player armour of" + to_string(chara->getAc()));
	return armourClass > attack;

}