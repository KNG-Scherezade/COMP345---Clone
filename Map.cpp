#include <time.h>

#include "Map.h"
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;


Map::Map()
{
	vector<vector<std::string>>  map = vector<vector<std::string>>();
	rows = 2;
	columns = 2;
	mapName = "Default";
	initializeMap();
}

Map::Map(Map * copyMap)
{
	vector<vector<std::string>> map = vector<vector<std::string>>();
	rows = copyMap->getRows();
	columns = copyMap->getColumns();
	mapName = copyMap->getMapName();

	// Make a copy of the map recieved as a param.
	for (int i = 0; i < rows; i++)
	{
		map.push_back(vector<string>());
		for (int j = 0; j < columns; j++)
		{
			map[i].push_back(copyMap->get(i,j));
		}
	}

}

Map::Map(int newRows, int newColumns) : rows(newRows), columns(newColumns)
{
	initializeMap();
}

Map::Map(int newRows, int newColumns, string newName) : rows(newRows), columns(newColumns), mapName(newName)
{
	initializeMap();
}

Map::~Map()
{
	deleteMap();
}

bool Map::validatePath()
{
	Node* startPointer = findStart();
	if (startPointer != 0) {
		Node* endPointer = findEnd();
		if (endPointer != 0) {
			bool result = findValidPath(startPointer, endPointer);

			// Delete pointers that will no longer be used
			delete startPointer;
			delete endPointer;
			startPointer = 0;
			endPointer = 0;

			return result;
		}
		else {
			cout << "Map is invalid. Cannot find end cell.\n";

			// Delete pointer that will no longer be used
			delete startPointer;
			startPointer = 0;

			return false;
		}
	}
	else {
		cout << "Map is invalid. Cannot find start cell.\n";
		return false;
	}
} 

//!Function fills a cell checking if there are properties to the char.
void Map::fillCell(int row, int column, string obj)
{
	// If the object is a start or end cell, make sure that one does not already exist.

	if (obj == "s" || obj == "e") {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (map[i][j] == obj) {
					cout << "Cannot have more than one start or end cell.";
					return;
				}
			}
		}
	}
	//If it's a chest, push it into the vector
	else if (obj == "&" || obj == "t") {
		ItemContainer* aChest = new ItemContainer(this, column, row);
		srand(time(NULL));
		chests.push_back(aChest);
	
	}
	else if (obj == "m") {
		monsters.push_back(new Monster(this, column, row));
	}
	map[row][column] = obj;
}

bool Map::isOccupied(int row, int column)
{
	return (map[row][column] != " ");
}

void Map::printMap()
{
	cout << mapName << " :\n";
	for (int i = 0; i < rows; i++) {
		cout << "\n[ ";
		for (int j = 0; j < columns; j++) {
			cout << map[i][j] << " ";
		}
		cout << "]";
	}
	cout << "\n";
}

void Map::setMapName(string newName)
{
	mapName = newName;
}

int Map::getRows()
{
	return rows;
}

int Map::getColumns()
{
	return columns;
}

string Map::getMapName()
{
	return mapName;
}
/*
char Map::getCharObject(int row, int column)
{
	if (row < rows && row >= 0) {
		if (column < columns && column >= 0) {
			return map[row][column];
		}
		else {
			cout << "Invalid column index\n";
			return 0;
		}
	}
	else {
		cout << "Invalid row index\n";
		return 0;
	}
}
*/
string Map::get(int row, int column)
{
	 return map[row][column];
}

void Map::initializeMap()
{
	// initialize rows and columns
	for (int i = 0; i < rows; i++)
	{
		map.push_back(vector<string>());
		for (int j = 0; j < columns; j++)
		{
			map[i].push_back(" ");
		}
	}
}

void Map::deleteMap() {
	// Not using any pointers, just self-deleting vector
	/*
	// Delete pointers to columns
	for (int i = 0; i < rows; ++i) {
		delete map[i];
	}

	// Delete rows
	delete map;
	*/
}

Node* Map::findStart()
{
	Node* startPointer = 0;
	int nodeIdIndex = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (map[i][j] == "s") {
				startPointer = new Node (nodeIdIndex, i, j);
				startPointer->setTraversable(true);
			}
			nodeIdIndex++;
		}
	}
	return startPointer;
}

Node* Map::findEnd()
{
	Node* endPointer = 0;
	int nodeIdIndex = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (map[i][j] == "e") {
				endPointer = new Node (nodeIdIndex, i, j, 0, true);
			}
			nodeIdIndex++;
		}
	}
	return endPointer;
}

bool Map::findValidPath(Node* startPointer, Node* endPointer)
{
	int id;
	int currentRow;
	int currentColumn;
	int heuristic;
	int const maxHeuristic = rows + columns;

	unordered_map<int, Node> parentMap;
	unordered_map<int, Node> closedMap;

	int const endNodeRow = endPointer->getRow();
	int const endNodeColumn = endPointer->getColumn();

	currentRow = startPointer->getRow();
	currentColumn = startPointer->getColumn();

	id = calculateNodeId(currentRow, currentColumn);
	heuristic = calculateHeuristic(currentRow, currentColumn, endNodeRow, endNodeColumn);

	startPointer->setHeuristic(heuristic);
	startPointer->setId(id);
	parentMap[id] = *startPointer;
	do {

		// Check if the current heuristic is 1, meaning that a valid path was found
		if (heuristic == 1) {
			return true;
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
			id = calculateNodeId(tempRow, currentColumn);

			// Check if the node was already found.
			bool notFound = (parentMap.find(id) == parentMap.end() && closedMap.find(id) == closedMap.end());
			if (notFound) {
				bool traversable = (map[tempRow][currentColumn] == " ");
				if (traversable) {
					heuristic = calculateHeuristic(tempRow, currentColumn, endNodeRow, endNodeColumn);
					parentMap[id] = Node(id, tempRow, currentColumn, heuristic, traversable);
				}
			}
		}

		// Check the bottom node
		tempRow = currentRow + 1;
		if (tempRow < rows) {
			id = calculateNodeId(tempRow, currentColumn);

			// Check if the node was already found.
			bool notFound = (parentMap.find(id) == parentMap.end() && closedMap.find(id) == closedMap.end());
			if (notFound) {
				bool traversable = (map[tempRow][currentColumn] == " ");
				if (traversable) {
					heuristic = calculateHeuristic(tempRow, currentColumn, endNodeRow, endNodeColumn);
					parentMap[id] = Node(id, tempRow, currentColumn, heuristic, traversable);
				}
			}
		}

		// Check the left node
		int tempColumn = currentColumn - 1;
		if (tempColumn > -1) {
			id = calculateNodeId(currentRow, tempColumn);

			// Check if the node was already found.
			bool notFound = (parentMap.find(id) == parentMap.end() && closedMap.find(id) == closedMap.end());
			if (notFound) {
				bool traversable = (map[currentRow][tempColumn] == " ");
				if (traversable) {
					heuristic = calculateHeuristic(currentRow, tempColumn, endNodeRow, endNodeColumn);
					parentMap[id] = Node(id, currentRow, tempColumn, heuristic, traversable);
				}
			}
		}

		// Check the right node
		tempColumn = currentColumn + 1;
		if (tempColumn < columns) {
			id = calculateNodeId(currentRow, tempColumn);

			// Check if the node was already found.
			bool notFound = (parentMap.find(id) == parentMap.end() && closedMap.find(id) == closedMap.end());
			if (notFound) {
				bool traversable = (map[currentRow][tempColumn] == " ");
				if (traversable) {
					heuristic = calculateHeuristic(currentRow, tempColumn, endNodeRow, endNodeColumn);
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
	} while (parentMap.size() != 0);

	cout << "Map is invalid. No valid path between the start and end cells exists.\n";
	return false;
}

int Map::calculateNodeId(int row, int column)
{
	return (rows * row + column);
}

int Map::calculateHeuristic(int row, int column, int endRow, int endColumn)
{
	return (abs(endRow - row) + abs(endColumn - column));
}





//! Returns an int code based off of the current standing square.
//! O is -2		 s is -1	# is 0		e is 1		& is 2		^ is 3		error space is the int of character ?
int Map::checkStandingSpace(int col, int row) {
	if (col < 0 || col >= columns || row < 0 || row >= rows) return '?';

	int spaceState;
	if (map[row][col] == "m") spaceState = -3;
	else if (map[row][col] == "O") spaceState = -2;
	else if (map[row][col] == "s") spaceState = -1;
	else if (map[row][col] == " ") spaceState = 0;
	else if (map[row][col] == "e") spaceState = 1;
	else if (map[row][col] == "&"|| map[row][col] == "t") spaceState = 2;
	else if (map[row][col] == "^") spaceState = 3;
	else if (map[row][col] == "O") spaceState = '?';
	else spaceState = '?';

	return spaceState;
}



//! Return a bool indicating whether or not the specified cell is occupied with a '#' or 'e' or 's'.
//! Reverses the order of arguments are reversed to represent x and y
bool Map::isFunctionallyOccupied(int col, int row)
{
	if (col < 0 || col >= columns || row < 0 || row >= rows) return true;
	else return (map[row][col] != " " && map[row][col] != "e" && map[row][col] != "s");
}


//! A currently unused function designed to check available squares within the characters moverate
void Map::createMoveSpaceVector(std::vector <std::vector<int>>* validSpaces, int initialPosition[], int moveRate) {
	int sideMove = 0;
	int upMove = moveRate;
	Node startPoint(calculateNodeId(initialPosition[1], initialPosition[0]), initialPosition[1], initialPosition[0]);

	//CARDINAL DIRECTION NORTH
	for (int i = 0; i < moveRate; i++) {
		for (int j = 0; j < sideMove; j++) {//from the side
			for (int k = -upMove; k < 0; k++) {//from the top
				Node endPoint(calculateNodeId(initialPosition[0] + j, initialPosition[1] + k), initialPosition[0] + j, initialPosition[1] + k);
				bool valid = findValidPath(&startPoint, &endPoint);
				if (valid) validSpaces->push_back({ initialPosition[0] + j, initialPosition[1] + k });
			}
			upMove++;
			sideMove++;
		}
	}
	//CARDINAL DIRECTION EAST
	for (int i = 0; i < moveRate; i++) {
		for (int k = -upMove; k < 0; k++) {//from the top
			for (int j = sideMove; j > 0; j--) {//from the side
				Node endPoint(calculateNodeId(initialPosition[0] + j, initialPosition[1] + k), initialPosition[0] + j, initialPosition[1] + k);
				bool valid = findValidPath(&startPoint, &endPoint);
				if (valid) validSpaces->push_back({ initialPosition[0] + j, initialPosition[1] + k });
			}
			upMove++;
			sideMove--;
		}
	}
	//CARDINAL DIRECTION SOUTH
	for (int i = 0; i < moveRate; i++) {
		for (int j = 0; j > -sideMove; j--) {//from the side
			for (int k = upMove; k > 0; k--) {//from the bottom
				Node endPoint(calculateNodeId(initialPosition[0] + j, initialPosition[1] + k), initialPosition[0] + j, initialPosition[1] + k);
				bool valid = findValidPath(&startPoint, &endPoint);
				if (valid) validSpaces->push_back({ initialPosition[0] + j, initialPosition[1] + k });
			}
			upMove--;
			sideMove--;
		}
	}
	//CARDINAL DIRECTION WEST
	for (int i = 0; i < moveRate; i++) {
		for (int k = 0; k < upMove; k++) {
			for (int j = 0; j > -sideMove; j--) {
				Node endPoint(calculateNodeId(initialPosition[0] + j, initialPosition[1] + k), initialPosition[0] + j, initialPosition[1] + k);
				bool valid = findValidPath(&startPoint, &endPoint);
				if (valid) validSpaces->push_back({ initialPosition[0] + j, initialPosition[1] + k });
			}
			upMove--;
			sideMove++;
		}
	}
}

void Map::setCharacterPosition(int pos[]) {
	characterPosition[0] = pos[0];
	characterPosition[1] = pos[1];
}
void Map::setCurrentSquare(int cState) {
	currentSquare = cState;
}

void Map::setCharacter(Character *chara) {
	character = chara;
}

ItemContainer* Map::getChestAtPosition(int x, int y) {
	for (int i = 0; i < chests.size(); i++) {
		if (chests.at(i)->getPosition()[0] == x && chests.at(i)->getPosition()[1] == y) {
			return chests.at(i);
		}
	}

	std::cout << "COULD NOT FIND CHEST AT " << x << " " << y << "\n";
	return new ItemContainer(this, 0, 0);
}

Monster* Map::getMonstersAtPosition(int x, int y) {
	for (int i = 0; i < monsters.size(); i++) {
		if (monsters.at(i)->getPosition()[0] == x && monsters.at(i)->getPosition()[1] == y) {
			return monsters.at(i);
		}
	}
	std::cout << "COULD NOT FIND MONSTER AT " << x << " " << y << "\n";
	return new Monster();
}

std::vector<ItemContainer*> Map::getChests() {
	return chests;
}

//stored as x y
int* Map::getCharacterPosition() {
	return characterPosition;
}

int Map::getCharacterLevel() {
	return character->getLevel();
}

vector<vector<std::string>> Map::getMap() {
	return map;
}
int Map::getCurrentSquare() {
	return currentSquare;
}
Character* Map::getCharacter() {
	return character;
}



void Map::attach(Observer* obs) {
	listeners.push_back(obs);
}
void Map::notify() {
	for each (Observer* obs in listeners)
	{
		obs->update();
	}
}