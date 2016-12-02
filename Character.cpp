//! @file Character.h
//! @author Patrick Nicoll 27218729
//! @brief Implementation of the class representing an instance of a character


#define CHARA_POSITION_X mapPtr->getCharacterPosition()[1]//cols are x
#define CHARA_POSITION_Y mapPtr->getCharacterPosition()[0]//rows are y

#define SET_POSITION mapPtr->setCharacterPosition(rtn)
#define SET_CURRENT_SQUARE mapPtr->setCurrentSquare(StandingOn(rtn[1], rtn[0]))

#define CHECK_SPACE_L StandingOn(CHARA_POSITION_X - 1, CHARA_POSITION_Y)
#define CHECK_SPACE_R StandingOn(CHARA_POSITION_X + 1, CHARA_POSITION_Y)
#define CHECK_SPACE_U StandingOn(CHARA_POSITION_X, CHARA_POSITION_Y - 1)
#define CHECK_SPACE_UL StandingOn(CHARA_POSITION_X - 1, CHARA_POSITION_Y - 1)
#define CHECK_SPACE_UR StandingOn(CHARA_POSITION_X + 1, CHARA_POSITION_Y - 1)
#define CHECK_SPACE_D StandingOn(CHARA_POSITION_X , CHARA_POSITION_Y + 1)
#define CHECK_SPACE_DL StandingOn(CHARA_POSITION_X - 1, CHARA_POSITION_Y + 1)
#define CHECK_SPACE_DR StandingOn(CHARA_POSITION_X + 1, CHARA_POSITION_Y + 1)

//#include "stdafx.h"
#include "Character.h"
#include "AbstractStrategy.h"
#include "ItemGenerator.h"

#include <random>
#include <iostream>
#include <vector>




//! Default no param constructor
Character::Character() {
	log = new Logger();
	Dice dice = Dice();
	level = 1;
	hpRollAccumulator = dice.rollD10();
	create();
	inventory = vector<Item*>();
}

//! Constructor that takes a level to initialize the stats accordingly
//! @param levelVal	Level of character
Character::Character(int levelVal) {
	log = new Logger();
	Dice dice = Dice();
	hpRollAccumulator = dice.rollD10();
	level = 1;
	create();
	inventory = vector<Item*>();

	//Print statements used for testing
	/*std::cout << "str: " << str << std::endl;
	std::cout << "dex: " << dex << std::endl;
	std::cout << "con: " << con << std::endl;*/

	for (int i = 1; i < levelVal; i++) {
		levelUp();
	}
	log->LogCharacter("Character named: " + name + " created at level: " + std::to_string(level));

}

Character::Character(Map* map) {
	log = new Logger();
	level = 1;
	Dice dice = Dice();
	hpRollAccumulator = dice.rollD10();
	create();

	mapPtr = map;
	moveable = (true);
	mapPtr->setCharacter(this);
	log->LogCharacter("Character named: " + name + " created at level: " + std::to_string(level));

}
//! To be used if constructor does not set the map pointer
//! also sets moster levels to player level
void Character::postInitialize(Map* map) {
	mapPtr = map;
	moveable = (true);
	mapPtr->setCharacter(this);
	mapPtr->characterInitialized = true;
	numAtks = 1 + (level / 5);
	//for each(ItemContainer* ic in mapPtr->getChests()) {
	//	ic->setItemLevels(level);
	//}
	//for each(Monster* mons in mapPtr->getMonsters()) {
	//	mons->levelUpStats(level);
	//}
	log->LogCharacter("Character named: " + name + " Initialized on map ");
}

//! Constructor that takes a level to initialize the stats accordingly
//!Takes map pointer
//! @param levelVal	Level of character
Character::Character(int levelVal, Map* map, AbstractStrategy* as) {
	dice = Dice();
	hpRollAccumulator = dice.rollD10();
	log = new Logger();
	create();

	this->as = as;

	//Print statements used for testing
	//std::cout << "str: " << str << std::endl;
	//std::cout << "dex: " << dex << std::endl;
	//std::cout << "con: " << con << std::endl;

	for (int i = 1; i < levelVal; i++) {
		levelUp();
	}

	mapPtr = map;
	moveable = (true);
	mapPtr->setCharacter(this);

}

//! Destructor
Character::~Character()
{
}

//!Sets the characters position on the map.
void Character::configurePosition() {
	if (mapPtr->getMap().size() != 0) {
		int rows = mapPtr->getRows();
		int cols = mapPtr->getColumns();
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (mapPtr->getMap()[i][j] == "s") {
					int rtn[] = { i , j };
					SET_POSITION;
					break;
				}
	}
}
//! Validates wheter the character has valid starting stats
//! @return Whether valid or not, true it is valid, false it is not
bool Character::validateNewCharacter()
{
	bool valid = true;

	if (str < 3 || str > 18)
		valid = false;
	if (dex < 3 || dex > 18)
		valid = false;
	if (con < 3 || con > 18)
		valid = false;
	if (intel < 3 || intel > 18)
		valid = false;
	if (wis < 3 || wis > 18)
		valid = false;
	if (cha < 3 || cha > 18)
		valid = false;

	return valid;
}

//! Method to call all the appropriate methods used during character creation.
void Character::create() {
	generateRandomStats();
	numAtks = 1 + level / 5;
	calculateHp();
	calculateAc();
	calculateBaseAttackBonus();
	calculateDamageBonus();
}
//! Method to call all the appropriate methods used during class creation.
void Character::createClass() {
	generateModifiers();
	calculateAc();
	calculateBaseAttackBonus();
	calculateDamageBonus();
}

//! Recalculates the modifiers
void Character::generateModifiers() {
	//Set modifiers
	str_mod = getModifier(str);
	dex_mod = getModifier(dex);
	con_mod = getModifier(con);
	intel_mod = getModifier(intel);
	wis_mod = getModifier(wis);
	cha_mod = getModifier(cha);
}

//! Generate the attribute values for the six major stats.
//! Values are between 3-18
void Character::generateRandomStats()
{
	// Will be used, but for testing purposes will hardcoded numbers will be set
	int stats[6];

	// create source of randomness, and initialize it with non-deterministic seed
	std::random_device r;
	std::seed_seq seed{ r(),r(),r(),r(),r(),r() };
	std::mt19937 eng{ seed };

	// a distribution that takes randomness and produces values in the range of 3 to 18
	std::uniform_int_distribution<> dist(3, 18);

	for (int i = 0; i < 6; i++) {
		stats[i] = dist(eng);
	}

	//Set stats
	str = stats[0];
	dex = stats[1];
	con = stats[2];
	intel = stats[3];
	wis = stats[4];
	cha = stats[5];

	//Set modifiers
	str_mod = getModifier(stats[0]);
	dex_mod = getModifier(stats[1]);
	con_mod = getModifier(stats[2]);
	intel_mod = getModifier(stats[3]);
	wis_mod = getModifier(stats[4]);
	cha_mod = getModifier(stats[5]);
}

//! Calculates the hitpoints of the character.
//! Hitpoints are calculated by adding the constitution modifier to the accumulator of hit points 
//! from dice rolls. 
void Character::calculateHp()
{
	hp = abs(con_mod) + hpRollAccumulator;
	maxHp = abs(con_mod) + hpRollAccumulator;
}

//! Calculates the armor class of the character.
//! Armor class is calculated by adding the dexterity modifier, armor bonus and shield bonus togther and then adding 10
void Character::calculateAc()
{
	ac = 10 + dex_mod;

	if (helmet != NULL)
		ac += helmet->getArmorClass();
	if (armor != NULL)
		ac += armor->getArmorClass();
	if (belt != NULL)
		ac += 0;
	if (boots != NULL)
		ac += boots->getArmorClass();
	if (shield != NULL)
		ac += shield->getArmorClass();
}

//! Calculates the base attack bonus of the character.
//! Base attack bonus is calculated by adding the strength modifier to the character level
void Character::calculateBaseAttackBonus()
{
	attackBonus = str_mod + level;
}

//! Calculates the damage bonus of the character.
//! Damage bonus is calculated based on the strength modifier of the character
void Character::calculateDamageBonus()
{
	damageBonus = str_mod;
}

//! Will increase attributes upon levelling up
void Character::levelUp() {
	level++;
	str++;
	dex++;
	con++;
	numAtks = 1 + level / 5;

	//Call relevant methods to update based on new stat increase
	str_mod = (getModifier(str));
	dex_mod = (getModifier(dex));
	con_mod = (getModifier(con));
	calculateHp();
	calculateAc();
	calculateBaseAttackBonus();
	calculateDamageBonus();
}

//! Determines modifier based on stat entered by evaluating which range it falls in
//! @param stat	Stat to determine range of
//! @return Value of the range the stat fell under
int Character::getModifier(int stat)
{
	int mod;

	if (stat <= 1)
		mod = -5;
	else if (stat <= 3)
		mod = -4;
	else if (stat <= 5)
		mod = -3;
	else if (stat <= 7)
		mod = -2;
	else if (stat <= 9)
		mod = -1;
	else if (stat <= 11)
		mod = 0;
	else if (stat <= 13)
		mod = 1;
	else if (stat <= 15)
		mod = 2;
	else if (stat <= 17)
		mod = 3;
	else if (stat <= 19)
		mod = 4;
	else
		mod = 5;

	return mod;
}

//! Reduces character's hitpoints based on damage inputed
//! @param damage	Damage to be taken away from hitpoints
void Character::hit(int damage) {
	hp -= damage;
	log->LogCharacter("Hit for " + std::to_string(damage));
}


//! Prints the character's inventory
void Character::printInventory()
{
	int ctr = 0;
	cout << "*** " << name << "'s Inventory ***" << endl;
	if (inventory.size() != 0) {
		for each (Item* i in inventory)
		{
			cout << "[" << ctr << "] " << i->getName() << endl;
			ctr++;
		}
		cout << "\n";
	}
	else
		cout << "Empty\n" << endl;
}

//! Prints the character's equipped items
void Character::printEquipped()
{
	if (helmet != NULL)
		cout << "[0] Helmet: " << helmet->getName() << endl;
	else
		cout << "[0] Helmet: None" << endl;
	if (armor != NULL)
		cout << "[1] Armor: " << armor->getName() << endl;
	else
		cout << "[1] Armor: None" << endl;
	if (ring != NULL)
		cout << "[2] Ring: " << ring->getName() << endl;
	else
		cout << "[2] Ring: None" << endl;
	if (belt != NULL)
		cout << "[3] Belt: " << belt->getName() << endl;
	else
		cout << "[3] Belt: None" << endl;
	if (boots != NULL)
		cout << "[4] Boots: " << boots->getName() << endl;
	else
		cout << "[4] Boots: None" << endl;
	if (shield != NULL)
		cout << "[5] Shield: " << shield->getName() << endl;
	else
		cout << "[5] Shield: None" << endl;
	if (weapon != NULL)
		cout << "[6] Weapon: " << weapon->getName() << endl;
	else
		cout << "[6] Weapon: None" << endl;

	cout << "\n";
}

//! Prints the stats of the character
void Character::printStats() {
	std::cout << "LVL " << getLevel() <<
		"\nHealth " << getHp() << "/" << getMaxHp() <<
		"\nCha " << getCha() <<
		"\nCon " << getCon() <<
		"\nDex " << getDex() <<
		"\nInt " << getIntel() <<
		"\nStr " << getStr() <<
		"\nWis " << getWis() << "\n";
}

//! Equip an item from the inventory. Item position in inventory is used to determine item that is intended to be equip
//! @param pos	Position of item in inventory
void Character::equip(int pos)
{
	Item* item = inventory[pos];
	std::string type = item->getType();

	// In cases where nothing is equip it will simply equip the new item
			// Otherwise it will replace the old equipment in that slot and place it in the inventory
			// Modifying stats dynamically
		if (type == "helmet") {
			if (helmet == NULL) {
				if (helmet == NULL)
					helmet = static_cast<Helmet*>(item);
				
			}
			else {
				inventory.push_back(helmet);
				wis -= helmet->getWisdom();
				intel -= helmet->getWisdom();
				helmet = static_cast<Helmet*>(item);
			}
			wis += helmet->getWisdom();
			intel += helmet->getWisdom();
			wis_mod = getModifier(wis);
			intel_mod = getModifier(intel);
			inventory.erase(inventory.begin() + pos);
			
		}
	if (type == "armor") {
		if (armor == NULL)
			armor = static_cast<Armor*>(item);
		else {
			inventory.push_back(armor);
			armor = static_cast<Armor*>(item);
		}
		inventory.erase(inventory.begin() + pos);
	}
	if (type == "ring") {
		int tempHp = 0;
		if (ring == NULL)
			ring = static_cast<Ring*>(item);
		else {
			inventory.push_back(ring);
			cha -= ring->getCharisma();
			con -= ring->getConstitution();
			str -= ring->getStrength();
			wis -= ring->getWisdom();
			if (hp != maxHp) {
				tempHp = hp;
			
			}
			ring = static_cast<Ring*>(item);
		}
		cha += ring->getCharisma();
		con += ring->getConstitution();
		str += ring->getStrength();
		wis += ring->getWisdom();
		cha_mod = getModifier(cha);
		con_mod = getModifier(con);
		str_mod = getModifier(str);
		wis_mod = getModifier(wis);
		calculateHp();
		if (tempHp != 0)
			if (tempHp < maxHp)
			hp = tempHp;
		calculateDamageBonus();
		calculateBaseAttackBonus();
		inventory.erase(inventory.begin() + pos);
	}
	if (type == "belt") {
		int tempHp = 0;
		if (belt == NULL)
			belt = static_cast<Belt*>(item);
		else {
			inventory.push_back(belt);
			con -= belt->getConstitution();
			str -= belt->getStrength();
			if (hp != maxHp) {
				tempHp = hp;
				
			}
			belt = static_cast<Belt*>(item);
		}
		con += belt->getConstitution();
		str += belt->getStrength();
		con_mod = getModifier(con);
		str_mod = getModifier(str);
		calculateHp();
		if (tempHp != 0)
			if (tempHp < maxHp)
			hp = tempHp;
		calculateDamageBonus();
		calculateBaseAttackBonus();
		inventory.erase(inventory.begin() + pos);
	}
	if (type == "boots") {
		if (boots == NULL)
			boots = static_cast<Boots*>(item);
		else {
			inventory.push_back(boots);
			dex -= boots->getDexterity();
			boots = static_cast<Boots*>(item);
		}
		dex += boots->getDexterity();
		dex_mod = getModifier(dex);
		inventory.erase(inventory.begin() + pos);
	}
	if (type == "shield") {
		if (shield == NULL)
			shield = static_cast<Shield*>(item);
		else {
			inventory.push_back(shield);
			shield = static_cast<Shield*>(item);
		}
		inventory.erase(inventory.begin() + pos);
	}
	if (type == "weapon") {
		if (weapon == NULL)
			weapon = static_cast<Weapon*>(item);
		else {
			inventory.push_back(weapon);
			weapon = static_cast<Weapon*>(item);
		}
		inventory.erase(inventory.begin() + pos);
	}
	calculateAc();
	log->LogCharacter(item->getName() + " equipped");
	
 }

// In cases where nothing is equip it will simply equip the new item
// Otherwise it will replace the old equipment in that slot and place it in the inventory
// Modifying stats dynamically
//! Unequip an item from the character. Slot represents which equipment slot is targeted for unequip
//! @param slot	Equipment slot to unequip
void Character::unequip(int slot)
{
	std::string type;

	switch (slot) {
	case 0:
		type = "helmet";
		break;
	case 1:
		type = "armor";
		break;
	case 2:
		type = "ring";
		break;
	case 3:
		type = "belt";
		break;
	case 4:
		type = "boots";
		break;
	case 5:
		type = "shield";
		break;
	case 6:
		type = "weapon";
		break;
	default:
		break;
	}

	if (type == "helmet") {
		if (helmet != NULL) {
			inventory.push_back(helmet);
			helmet = NULL;
		}
		else
			cout << "There is nothing in that slot." << endl;
	}
	if (type == "armor") {
		if (armor != NULL) {
			inventory.push_back(armor);
			armor = NULL;
		}
		else
			cout << "There is nothing in that slot." << endl;
	}
	if (type == "ring") {
		if (ring != NULL) {
			inventory.push_back(ring);
			ring = NULL;
		}
		else
			cout << "There is nothing in that slot." << endl;
	}
	if (type == "belt") {
		if (belt != NULL) {
			inventory.push_back(belt);
			belt = NULL;
		}
		else
			cout << "There is nothing in that slot." << endl;
	}
	if (type == "boots") {
		if (boots != NULL) {
			inventory.push_back(boots);
			boots = NULL;
		}
		else
			cout << "There is nothing in that slot." << endl;
	}
	if (type == "shield") {
		if (shield != NULL) {
			inventory.push_back(shield);
			shield = NULL;
		}
		else
			cout << "There is nothing in that slot." << endl;
	}
	if (type == "weapon") {
		if (weapon != NULL) {
			inventory.push_back(weapon);
			weapon = NULL;
		}
		else
			cout << "There is nothing in that slot." << endl;
	}
}

void Character::addToInventory(Item* item) {
	inventory.push_back(item);
	log->LogCharacter(item->getName() + " added to inventory");
}




//////////////////////MOVEMENT


bool Character::checkMonsters(std::string moveDir) {
	for each(Monster* mon in mapPtr->getMonsters()) {
		if (moveDir == "l" || moveDir == "L") {
			if (CHARA_POSITION_X - 1 == mon->position[0], CHARA_POSITION_Y == mon->position[1]) {
				return false;
			}
			else {
				return true;
			}
		}
		else if (moveDir == "r" || moveDir == "R") {
			if (CHARA_POSITION_X == mon->position[0], CHARA_POSITION_Y == mon->position[1]) {
				moveable = (false);
				return false;
			}
			else {
				return true;
			}
		}
		else if (moveDir == "u" || moveDir == "U") {
			if (CHARA_POSITION_X == mon->position[0], CHARA_POSITION_Y - 1 == mon->position[1]) {
				return false;
			}
			else {
				return true;
			}
		}
		else if (moveDir == "d" || moveDir == "D") {
			if (CHARA_POSITION_X == mon->position[0], CHARA_POSITION_Y + 1 == mon->position[1]) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			moveable = false;
		}
	}
}

//!Checks if the character can make a valid move on the map
void Character::checkMove(std::string moveDir) {
	moveable = (true); //negative conditions set false
	int rtn[2];
	rtn[1] = CHARA_POSITION_X;
	rtn[0] = CHARA_POSITION_Y;
	if (moveDir == "l" || moveDir == "L") {
		if (mapPtr->isFunctionallyOccupied(CHARA_POSITION_X - 1, CHARA_POSITION_Y) && checkMonsters(moveDir)) {
			moveable = (false);
		}
		else {
			rtn[1] = CHARA_POSITION_X - 1;
			rtn[0] = CHARA_POSITION_Y;
		}
	}
	else if (moveDir == "r" || moveDir == "R") {
		if (mapPtr->isFunctionallyOccupied(CHARA_POSITION_X + 1, CHARA_POSITION_Y) && checkMonsters(moveDir)) {
			moveable = (false);
		}
		else {
			rtn[1] = CHARA_POSITION_X + 1;
			rtn[0] = CHARA_POSITION_Y;
		}
	}
	else if (moveDir == "u" || moveDir == "U") {
		if (mapPtr->isFunctionallyOccupied(CHARA_POSITION_X, CHARA_POSITION_Y - 1) && checkMonsters(moveDir)) {
			moveable = (false);
		}
		else {
			rtn[1] = CHARA_POSITION_X;
			rtn[0] = CHARA_POSITION_Y - 1;
		}
	}
	else if (moveDir == "d" || moveDir == "D") {
		if (mapPtr->isFunctionallyOccupied(CHARA_POSITION_X, CHARA_POSITION_Y + 1) && checkMonsters(moveDir)) {
			moveable = (false);
		}
		else {
			rtn[1] = CHARA_POSITION_X;
			rtn[0] = CHARA_POSITION_Y + 1;
		}
	}
	else {
		moveable = (false);
	}
	log->LogMap("Checked if moving square was occupied");
	//std::cout << rtn[1] << " " << rtn[0] << "\n";
	SET_POSITION;
	log->LogMap("Positions was set on map at " + to_string(rtn[0]) + " " + to_string(rtn[1]));
	//Set your location on the map
	SET_CURRENT_SQUARE;
	log->LogMap("Current square was set on map");
	mapPtr->notify();
}


//!Checks what the character is looking at and returns an ID from map function checkStandingSpace(col, row)
int Character::checkAttack(std::string lookDir) {
	int spaceID = '?';
	std::string finalLookDir;
	if (lookDir == "l" || lookDir == "L") {
		finalLookDir = "l";
		spaceID = CHECK_SPACE_L;
	}
	else if (lookDir == "r" || lookDir == "R") {
		finalLookDir = "r";
		spaceID = CHECK_SPACE_R;
	}
	else if (lookDir == "u" || lookDir == "U") {
		std::cout << "Enter l for diagonal left, r for diagonal right and u for straight up\n";
		std::cin >> lookDir;
		if (lookDir == "l" || lookDir == "L") {
			finalLookDir = "ul";
			spaceID = CHECK_SPACE_UL;
		}
		else if (lookDir == "r" || lookDir == "R") {
			finalLookDir = "ur";
			spaceID = CHECK_SPACE_UR;
		}
		else if (lookDir == "u" || lookDir == "U") {
			finalLookDir = "u";
			spaceID = CHECK_SPACE_U;
		}
		else
			spaceID = '?';
	}
	else if (lookDir == "d" || lookDir == "D") {
		std::cout << "Enter l for diagonal left, r for diagonal right and d for straight down\n";
		std::cin >> lookDir;
		if (lookDir == "l" || lookDir == "L") {
			finalLookDir = "dl";
			spaceID = CHECK_SPACE_DL;
		}
		else if (lookDir == "r" || lookDir == "R") {
			finalLookDir = "dr";
			spaceID = CHECK_SPACE_DR;
		}
		else if (lookDir == "d" || lookDir == "D") {
			finalLookDir = "d";
			spaceID = CHECK_SPACE_D;
		}
		else {
			spaceID = '?';
		}
	}
	return spaceID;
}


//!Checks what the character is looking at and returns an ID from map function checkStandingSpace(col, row)
int Character::checkLook(std::string lookDir) {
	int spaceID = '?';
	std::string finalLookDir;
	if (lookDir == "l" || lookDir == "L") {
		finalLookDir = "l";
		spaceID = CHECK_SPACE_L;
	}
	else if (lookDir == "r" || lookDir == "R") {
		finalLookDir = "r";
		spaceID = CHECK_SPACE_R;
	}
	else if (lookDir == "u" || lookDir == "U") {
		std::cout << "Enter l for diagonal left, r for diagonal right and u for straight up\n";
		std::cin >> lookDir;
		if (lookDir == "l" || lookDir == "L") {
			finalLookDir = "ul";
			spaceID = CHECK_SPACE_UL;
		}
		else if (lookDir == "r" || lookDir == "R") {
			finalLookDir = "ur";
			spaceID = CHECK_SPACE_UR;
		}
		else if (lookDir == "u" || lookDir == "U") {
			finalLookDir = "u";
			spaceID = CHECK_SPACE_U;
		}
		else
			spaceID = '?';
	}
	else if (lookDir == "d" || lookDir == "D") {
		std::cout << "Enter l for diagonal left, r for diagonal right and d for straight down\n";
		std::cin >> lookDir;
		if (lookDir == "l" || lookDir == "L") {
			finalLookDir = "dl";
			spaceID = CHECK_SPACE_DL;
		}
		else if (lookDir == "r" || lookDir == "R") {
			finalLookDir = "dr";
			spaceID = CHECK_SPACE_DR;
		}
		else if (lookDir == "d" || lookDir == "D") {
			finalLookDir = "d";
			spaceID = CHECK_SPACE_D;
		}
		else {
			spaceID = '?';
		}
	}

	if (finalLookDir == "l")	checkInteraction(CHARA_POSITION_Y, CHARA_POSITION_X - 1, spaceID);
	else if (finalLookDir == "r")checkInteraction(CHARA_POSITION_Y, CHARA_POSITION_X + 1, spaceID);
	else if (finalLookDir == "u")checkInteraction(CHARA_POSITION_Y - 1, CHARA_POSITION_X, spaceID);
	else if (finalLookDir == "ul")checkInteraction(CHARA_POSITION_Y - 1, CHARA_POSITION_X - 1, spaceID);
	else if (finalLookDir == "ur")checkInteraction(CHARA_POSITION_Y - 1, CHARA_POSITION_X + 1, spaceID);
	else if (finalLookDir == "d")checkInteraction(CHARA_POSITION_Y + 1, CHARA_POSITION_X, spaceID);
	else if (finalLookDir == "dr")checkInteraction(CHARA_POSITION_Y + 1, CHARA_POSITION_X + 1, spaceID);
	else if (finalLookDir == "dl")checkInteraction(CHARA_POSITION_Y + 1, CHARA_POSITION_X - 1, spaceID);

	return spaceID;
}


//!Based off of what happens in checklook, this function alters the state of the map, displays a message or does other actions.
//!Eg. the character makes acts on a chest so it should get the map to make a change.(Only map related features)
//! ex. the character interacts with a chest so the chest flag should be set.
void Character::checkInteraction(int row, int col, int type) {
	mapPtr->notify();
	switch (type) {
	case -3:
		lastInteractedMonster = mapPtr->getMonstersAtPosition(col, row);
		break;
	case -2:
		std::cout << "\nT'IS PILLAR\n";
		break;
	case -1:
		std::cout << "\nT'IS AN ENTRANCE\n";
		break;
	case 0:
		std::cout << "\nT'IS EMPTY\n";
		break;
	case 1:
		std::cout << "\nT'IS AN EXIT\n";
		break;
	case 2:
		lastOpenedChest = mapPtr->getChestAtPosition(col, row);
		break;
	case 3:
		std::cout << "\nT'IS AN OPEN CHEST\n";
		break;
	default:
		std::cout << "\nT'IS A WALL\n";
	}
}


std::string Character::toString() {
	return ("Name: " + name + "\nLevel: " + std::to_string(level) + "\nstr:" + std::to_string(str) + "\ndex:" + std::to_string(dex) + "\ncon" + std::to_string(con)
		+ "\nInt" + std::to_string(intel) + "\nwis" + std::to_string(wis) + "\ncha:" + std::to_string(cha) + "\nHP: " + std::to_string(hp) + "\nmax HP: " + std::to_string(maxHp) + "\n");
}


//! A character specific usage of map's checkStandingSpace(int col,int row) function
int Character::StandingOn(int col, int row) {
	return mapPtr->checkStandingSpace(col, row);
}

bool Character::getMoveable() {
	return moveable;
}

void Character::setMoveable(bool move) {
	moveable = move;
}

int Character::executeStrategy() {
	return as->decideAction(this);
}

void Character::setStrategy(AbstractStrategy* strat) {
	as = strat;
	log->LogCharacter("Character was given its strategy");
}
