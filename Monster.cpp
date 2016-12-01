#include "Monster.h"
#include <iostream>
#include <string>
#include <unordered_map>

//!@file Monster.cpp
//!  @brief Implementation of DnD monster class
//!
//!  This class is a monster that the character will combat
//!  It contains all basic stats that a monster has in D20

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
	hitpoints = m_level;
	attack = m_level;
	level = m_level;
	dex = m_level;
	str = m_level;
	con = m_level;
	intel = m_level;
	wis = m_level;
	cha = m_level;
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
			for each(std::vector<int> coord in pathToCharacter) {
				std::cout << coord.at(0) << " x " << coord.at(1) << " y " << std::endl;
			}
			std::cout << "---Found---\n";

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

