#pragma once
#include <iostream>
#include "CharacterDriver.h"
#include "GenericMapItem.h"

//Relevant documents are not in the "Old Material" filter
//This uses the classes from the combined project.
//
//When a player controled character is moved, it updates the location.
//If an enemy is right in front of the player and the character does not move, 
//the character will check to see if it is attacked.
//
//If the user has entered the number 3 followed by e followed by the direction of the enemy, 
//then the enemy will attack and have its "attacked boolean se to true".

//! in the d20 rule set all character can move around a map and attack enemies.
//! this implementation of the strategy sets the groundwork for this by giving monsters and players
//! the ability to control their character on the map and finally implementing an element of gameplay into the game.


class Character;

class AbstractStrategy
{
public:
	AbstractStrategy();
	~AbstractStrategy();

	//! Various logical procedures decide what kind of action should be taken for the given mapitem
	virtual int decideAction(GenericMapItem* chara) = 0;
	//!If the user is human, an interaction with a monster causes an attack. If the user is a monster,
	//!it does a check to see if it can attack
	virtual void attack(GenericMapItem* chara) = 0;
	//!Movement is caried out with boolean checks for humans
	//!For monsters, a modification of the pathfinding algorithm for map validation is used.
	virtual void move(GenericMapItem* chara) = 0;
	//!Humans interact with the 3 key and a direction. This is different from the attack, yet uses the same commands
	//! Monsters can not interact.
	virtual int interact(GenericMapItem* chara) = 0;
};

