#include "Monster.h"
#include <iostream>
#include <string>
#include <unordered_map>

//!@file Monster.cpp
//!  @brief Implementation of DnD monster class
//!
//!  This class is a monster that the character will combat
//!  It contains all basic stats that a monster has in D20

//!

//! Default constructor sets attributes to level 1
Monster::Monster()
{
	hitpoints = 1;
	attack = 1;
	level = 1;
	dex = 1;
	str = 1;
	con = 1;
	intel = 1;
	wis = 1;
	cha = 1;
	type = "Not a Monster";
	dead = false;
}

//! Constructor assigns stats based on level
//! @param m_level sets stats based on this level
Monster::Monster(int m_level)
{
	levelUpStats(m_level);
	type = "monster";
	dead = false;
}

Monster::Monster(Map* map, int x, int y)
{
	position[0] = x;
	position[1] = y;
	mapPtr = map;

	hitpoints = 1;
	attack = 1;
	level = 1;
	dex = 1;
	str = 1; 
	con = 1;
	intel = 1;
	wis = 1;
	cha = 1;
	type = "monster";
	dead = false;
}

//! Constructor assigns stats based on level
//! @param m_level sets stats based on this level
Monster::Monster(Map* map, int x, int y, int m_level, AbstractStrategy* as)
{
	this->as = as;

	position[0] = x;
	position[1] = y;
	mapPtr = map;
	levelUpStats(m_level);
	type = "monster";
	dead = false;
}

Monster::~Monster(){}

void Monster::setStrategy(AbstractStrategy* as) {
	this->as = as;
}
void Monster::executeStrategy() {
	as->decideAction(this);
}

//! Assigns stats based on level
//! @param m_level sets stats based on this level
void Monster::levelUpStats(int m_level)
{
	hitpoints = m_level * 1.2;
	currentHP = m_level * 1.2;
	attack = m_level * 1.2;
	level = m_level ;
	dex = m_level * 1.2;
	str = m_level * 2;
	con = m_level * 1.2;
	intel = m_level* 1.2;
	wis = m_level* 1.2;
	cha = m_level* 1.2;
	ac = calculateAc();
}

//! Calculates the base attack bonus of the character.
//! Base attack bonus is calculated by adding the strength modifier to the character level



int Monster::getModifier(int stat)
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

int Monster::calculateBaseAttackBonus()
{
	int str_mod = (getModifier(str));
	return str_mod + level;
}

int Monster::calculateAc()
{
	return 10 + getModifier(dex);
}

std::string Monster::toString() {
	return "MONSTER:\nHP: " + std::to_string(currentHP) + "/" + std::to_string(hitpoints) + "\nATTACK: " + std::to_string(attack) + "\nLEVEL: " + std::to_string(level)
		+ "\nDEX: " + std::to_string(dex) + "\nSTR: " + std::to_string(str) + "\nCON: " + std::to_string(con) + "\nINTEL: "
			+ std::to_string(intel) + "\nWIS: " + std::to_string(wis) + "\nCHA: " + std::to_string(cha);
}

void Monster::createPathToCharacter(Node* startPointer, Node* endPointer) {
	int id;
	int currentRow;
	int currentColumn;
	int heuristic;
	int const maxHeuristic = mapPtr->getRows() + mapPtr->getColumns();

	unordered_map<int, Node> parentMap;
	unordered_map<int, Node> closedMap;

	int const endNodeRow = endPointer->getRow();
	int const endNodeColumn = endPointer->getColumn();

	currentRow = startPointer->getRow();
	currentColumn = startPointer->getColumn();

	id = mapPtr->calculateNodeId(currentRow, currentColumn);
	heuristic = mapPtr->calculateHeuristic(currentRow, currentColumn, endNodeRow, endNodeColumn);

	startPointer->setHeuristic(heuristic);
	startPointer->setId(id);
	parentMap[id] = *startPointer;
	parentMap[id] = *startPointer;
	do {

		// Check if the current heuristic is 1, meaning that a valid path was found
		if (heuristic == 1) {
			return;
		}

		// Remove current node from parentMap and add it to closedMap
		closedMap[id] = parentMap[id];
		parentMap.erase(id);

		currentRow = closedMap[id].getRow();
		currentColumn = closedMap[id].getColumn();
		// The following code is very similar in all four if statements. Only the row or the column changes.
		// Ideally, it should be placed within a private method and sent the row and column. However, I would then
		// need to figure out an efficient way to send the parentMap without wasting resources. One way to do this
		// would be to use a pointer but I decided not to because I thought it would waste too many resources in this case.

		// Check the top node
		int tempRow = currentRow - 1;
		if (tempRow > -1) {
			id = mapPtr->calculateNodeId(tempRow, currentColumn);

			// Check if the node was already found.
			bool notFound = (parentMap.find(id) == parentMap.end() && closedMap.find(id) == closedMap.end());
			if (notFound) {
				bool traversable = (mapPtr->getMap()[tempRow][currentColumn] == " " || mapPtr->getMap()[tempRow][currentColumn] == "e" || mapPtr->getMap()[tempRow][currentColumn] == "s");
				if (traversable) {
					heuristic = mapPtr->calculateHeuristic(tempRow, currentColumn, endNodeRow, endNodeColumn);
					parentMap[id] = Node(id, tempRow, currentColumn, heuristic, traversable);
				}
			}
		}

		// Check the bottom node
		tempRow = currentRow + 1;
		if (tempRow < mapPtr->getRows()) {
			id = mapPtr->calculateNodeId(tempRow, currentColumn);

			// Check if the node was already found.
			bool notFound = (parentMap.find(id) == parentMap.end() && closedMap.find(id) == closedMap.end());
			if (notFound) {
				bool traversable = (mapPtr->getMap()[tempRow][currentColumn] == " " || mapPtr->getMap()[tempRow][currentColumn] == "e" || mapPtr->getMap()[tempRow][currentColumn] == "s");
				if (traversable) {
					heuristic = mapPtr->calculateHeuristic(tempRow, currentColumn, endNodeRow, endNodeColumn);
					parentMap[id] = Node(id, tempRow, currentColumn, heuristic, traversable);
				}
			}
		}

		// Check the left node
		int tempColumn = currentColumn - 1;
		if (tempColumn > -1) {
			id = mapPtr->calculateNodeId(currentRow, tempColumn);

			// Check if the node was already found.
			bool notFound = (parentMap.find(id) == parentMap.end() && closedMap.find(id) == closedMap.end());
			if (notFound) {
				bool traversable = (mapPtr->getMap()[currentRow][tempColumn] == " " || mapPtr->getMap()[currentRow][tempColumn] == "e" || mapPtr->getMap()[currentRow][tempColumn] == "s");
				if (traversable) {
					heuristic = mapPtr->calculateHeuristic(currentRow, tempColumn, endNodeRow, endNodeColumn);
					parentMap[id] = Node(id, currentRow, tempColumn, heuristic, traversable);
				}
			}
		}

		// Check the right node
		tempColumn = currentColumn + 1;
		if (tempColumn < mapPtr->getColumns()) {
			id = mapPtr->calculateNodeId(currentRow, tempColumn);

			// Check if the node was already found.
			bool notFound = (parentMap.find(id) == parentMap.end() && closedMap.find(id) == closedMap.end());
			if (notFound) {
				bool traversable = (mapPtr->getMap()[currentRow][tempColumn] == " " || mapPtr->getMap()[currentRow][tempColumn] == "e" || mapPtr->getMap()[currentRow][tempColumn] == "s");
				if (traversable) {
					heuristic = mapPtr->calculateHeuristic(currentRow, tempColumn, endNodeRow, endNodeColumn);
					parentMap[id] = Node(id, currentRow, tempColumn, heuristic, traversable);
				}
			}
		}

		heuristic = maxHeuristic;

		// Get details of parent with smallest heuristic
		for (auto &node : parentMap) {
			if (node.second.getHeuristic() <= heuristic) {
				heuristic = node.second.getHeuristic();
				id = node.first;
			}
		}
		//std::cout << "---\n";
		pathToCharacter.push_back({ parentMap[id].getColumn(), parentMap[id].getRow() });

	} while (parentMap.size() != 0);

	cout << "Map is invalid. No valid path between the start and end cells exists.\n";

}

int Monster::StandingOn(int col, int row) {
	return mapPtr->checkStandingSpace(col, row);
}

//! generic observer functions done in super
void Monster::notify() {
	for each(Observer* obs in listeners) {
		obs->update();
	}
}
void Monster::attach(Observer* obs) {
	listeners.push_back(obs);
}

