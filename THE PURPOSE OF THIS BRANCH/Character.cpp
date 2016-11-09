#include "Character.h"

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

Character::Character(Map *map)
{
	mapPtr = map;
	moveable = (true);
	mapPtr->setCharacter(this);
	level = 9001;
}
Character::~Character()
{
}

//!Sets the characters position on the map.
void Character::configurePosition() {
	if (mapPtr->getMap() != nullptr) {
		int rows = mapPtr->getRows();
		int cols = mapPtr->getColumns();
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (mapPtr->getMap()[i][j] == 's') {
					int rtn[] = { i , j };
					SET_POSITION;
				}
	}
}

//!Checks if the character can make a valid move on the map
void Character::checkMove(char moveDir) {
	moveable = (true); //negative conditions set false
	int rtn[2];
	rtn[1] = CHARA_POSITION_X;
	rtn[0] = CHARA_POSITION_Y;
	if (moveDir == 'l' || moveDir == 'L') {
		if (mapPtr->isFunctionallyOccupied(CHARA_POSITION_X - 1, CHARA_POSITION_Y)) {
			moveable = (false);
		 }
		else {
			rtn[1] = CHARA_POSITION_X  - 1;
			rtn[0] = CHARA_POSITION_Y;
		}
	}
	else if (moveDir == 'r' || moveDir == 'R') {
		if (mapPtr->isFunctionallyOccupied(CHARA_POSITION_X + 1, CHARA_POSITION_Y)) {
			moveable = (false);
		}
		else {
			rtn[1] = CHARA_POSITION_X + 1;
			rtn[0] = CHARA_POSITION_Y;
		}
	}
	else if (moveDir == 'u' || moveDir == 'U') {
		if (mapPtr->isFunctionallyOccupied(CHARA_POSITION_X, CHARA_POSITION_Y - 1)) {
			moveable = (false);
		}
		else {
			rtn[1] = CHARA_POSITION_X;
			rtn[0] = CHARA_POSITION_Y - 1;
		}
	}
	else if (moveDir == 'd' || moveDir == 'D') {
		if (mapPtr->isFunctionallyOccupied(CHARA_POSITION_X, CHARA_POSITION_Y + 1)) {
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
	//std::cout << rtn[1] << " " << rtn[0] << "\n";
	SET_POSITION;
	//Set your location on the map
	SET_CURRENT_SQUARE;
	mapPtr->notify();
}

//!Checks what the character is looking at and returns an ID from map function checkStandingSpace(col, row)
int Character::checkLook(char lookDir) {
	int spaceID = '?';
	std::string finalLookDir;
	if (lookDir == 'l' || lookDir == 'L') {
		finalLookDir = "l";
		spaceID = CHECK_SPACE_L;
	}
	else if (lookDir == 'r' || lookDir == 'R') {
		finalLookDir = "r";
		spaceID = CHECK_SPACE_R;
	}
	else if (lookDir == 'u' || lookDir == 'U') {
		std::cout << "Enter l for diagonal left, r for diagonal right and u for straight up\n";
		std::cin >> lookDir;
		if (lookDir == 'l' || lookDir == 'L') {
			finalLookDir = "ul";
			spaceID = CHECK_SPACE_UL;
		}
		else if (lookDir == 'r' || lookDir == 'R') {
			finalLookDir = "ur";
			spaceID = CHECK_SPACE_UR;
		}
		else if (lookDir == 'u' || lookDir == 'U') {
			finalLookDir = "u";
			spaceID = CHECK_SPACE_U;
		}
		else
			spaceID = '?';
	}
	else if (lookDir == 'd' || lookDir == 'D') {
		std::cout << "Enter l for diagonal left, r for diagonal right and d for straight down\n";
		std::cin >> lookDir;
		if (lookDir == 'l' || lookDir == 'L') {
			finalLookDir = "dl";
			spaceID = CHECK_SPACE_DL;
		}
		else if (lookDir == 'r' || lookDir == 'R') {
			finalLookDir = "dr";
			spaceID = CHECK_SPACE_DR;
		}
		else if (lookDir == 'd' || lookDir == 'D') {
			finalLookDir = "d";
			spaceID = CHECK_SPACE_D;
		}
		else {
			spaceID = '?';
		}
	}

	if (finalLookDir == "l") checkInteraction(CHARA_POSITION_Y, CHARA_POSITION_X - 1, spaceID);
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
std::string Character::checkInteraction(int row, int col, int type) {
	mapPtr->notify();
	switch (type) {
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
		mapPtr->getChestAtPosition(col, row)->setOpen(true);
		mapPtr->notify();
		mapPtr->getChestAtPosition(col, row)->notify();
		break;
	case 3:
		std::cout << "\nT'IS AN OPEN CHEST\n";
		break;
	default:
		std::cout << "\nT'IS A WALL\n";
	}
	return "";
}

//! A character specific usage of map's checkStandingSpace(int col,int row) function
int Character::StandingOn(int col,int row) {
	return mapPtr->checkStandingSpace(col, row);
}

//! Getters and setters for private vars
int Character::getLevel() {
	return level;
}

bool Character::getMoveable() {
	return moveable;
}
void Character::setLevel(int lvl) {
	level = lvl;
}
void Character::setMoveable(bool move) {
	moveable = move;
}

