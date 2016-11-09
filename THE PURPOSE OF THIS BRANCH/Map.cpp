#include "Map.h" // AKA subject or model

//! Private fields
int rows;
int columns;
char **map;

Map::Map() : rows(3), columns(3), currentSquare('?') {
	srand(time(0));
}
Map::Map(int newRows, int newColumns) : rows(newRows), columns(newColumns), currentSquare('?'){
	srand(time(0));
}

//! Allocates memory for the map and sets the cell to empty values.
//!Creates chest, entrance and exit spaces.
void Map::initializeMap()
{
	// Initialize rows
	map = new char*[rows];

	// Initialize pointers to columns
	for (int i = 0; i < rows; ++i) {
		map[i] = new char[columns];
	}

	//Create an arbritray startpoint, endpoint, chest and pillar for testing
	do{
		// Set default empty value for all the elemts in the map matrix
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				map[i][j] = '#';
			}
		}

		int chestLocation[2]{ rand() % (rows), rand() % (columns) };
		map[chestLocation[0]][chestLocation[1]] = '&';

		chests.clear();
		chestObservers.clear();
		//memory leak on index 0
		chests.push_back(new Chest(this, chestLocation[1],chestLocation[0]));
		chests.at(0)->updateChestState();
		chestObservers.push_back(new ChestObserver(chests.at(0)));

		map[rand() % (rows)][rand() % (columns)] = 'O';

		int startCoords[2];
		startCoords[0] = rand() % (rows);
		startCoords[1] = rand() % (columns);
		map[startCoords[0]][startCoords[1]] = 's';

		setCharacterPosition(startCoords);
		map[rand() % (rows)][rand() % (columns)] = 'e';

	} while (!validatePath());

	notify();
}


void Map::fillCell(int row, int col, char obj)
{
	map[row][col] = obj;
	notify();
}

//! Return a bool indicating whether or not the specified cell is occupied with a '#' or 'e' or 's'.
//! Reverses the order of arguments are reversed to represent x and y
bool Map::isFunctionallyOccupied(int col, int row)
{
	if (col < 0 || col >= columns || row < 0 || row >= rows) return true;
	else return (map[row][col] != '#' && map[row][col] != 'e' && map[row][col] != 's');
}

//! Return a bool indicating whether or not the specified cell is occupied.
bool Map::isOccupied(int row, int col)
{
	return (map[row][col] != '#');
}

//! Returns an int code based off of the current standing square.
//! O is -2		 s is -1	# is 0		e is 1		& is 2		^ is 3		error space is the int of character ?
int Map::checkStandingSpace(int col, int row) {
	if (col < 0 || col >= columns || row < 0 || row >= rows) return '?';
	
	int spaceState;
	if (map[row][col] == 'O') spaceState = -2;
	else if (map[row][col] == 's') spaceState = -1;
	else if (map[row][col] == '#') spaceState = 0;
	else if (map[row][col] == 'e') spaceState = 1;
	else if (map[row][col] == '&') spaceState = 2;
	else if (map[row][col] == '^') spaceState = 3;
	else spaceState = '?';

	return spaceState;
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



//! Dealocates memory for the map.
void Map::deleteMap() {
	// Delete pointers to columns
	for (int i = 0; i < rows; ++i) {
		delete map[i];
	}

	// Delete rows
	delete map;
	//notify();
}

//! Searches for the start cell. Returns a pointer to a Node representing the cell.
Node* Map::findStart()
{
	Node* startPointer = 0;
	int nodeIdIndex = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (map[i][j] == 's') {
				startPointer = new Node(nodeIdIndex, i, j);
				startPointer->setTraversable(true);
			}
			nodeIdIndex++;
		}
	}
	return startPointer;
}

//! Searches for the end cell. Returns a pointer to a Node representing the cell.
Node* Map::findEnd()
{
	Node* endPointer = 0;
	int nodeIdIndex = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (map[i][j] == 'e') {
				endPointer = new Node(nodeIdIndex, i, j, 0, true);
			}
			nodeIdIndex++;
		}
	}
	return endPointer;
}

//! General method for validating the path. First calls a method that verifies that the map has a start
//! and an end. Then calls another method to check if a valid path exists within the map.
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
			cout << "\nMap is invalid. Cannot find end cell.";

			// Delete pointer that will no longer be used
			delete startPointer;
			startPointer = 0;

			return false;
		}
	}
	else {
		cout << "\nMap is invalid. Cannot find start cell.";
		return false;
	}
} 

//! Searches for a valid path within the map.
bool Map::findValidPath(Node* startPointer, Node* endPointer)
{
	int id;
	int currentRow;
	int currentColumn;
	int heuristic;
	int maxHeuristic = rows + columns;

	unordered_map<int, Node> parentMap;
	unordered_map<int, Node> closedMap;

	int endNodeRow = endPointer->getRow();
	int endNodeColumn = endPointer->getColumn();

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

		// Check the top node
		int tempRow = currentRow - 1;
		if (tempRow > -1) {
			id = calculateNodeId(tempRow, currentColumn);

			// Check if the node was already found.
			bool notFound = (parentMap.find(id) == parentMap.end() && closedMap.find(id) == closedMap.end());
			if (notFound) {
				bool traversable = (map[tempRow][currentColumn] == ' ');
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
				bool traversable = (map[tempRow][currentColumn] == '#');
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
				bool traversable = (map[currentRow][tempColumn] == '#');
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
				bool traversable = (map[currentRow][tempColumn] == '#');
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



//! SETTERS FOR FIELDS




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
//! GETTERS FOR FIELDS

//stored as x y
int* Map::getCharacterPosition() {
	return characterPosition;
}

int Map::getCharacterLevel() {
	return character->getLevel();
}

int Map::getRows() {
	return rows;
}
int Map::getColumns() {
	return columns;
}
char** Map::getMap() {
	return map;
}
int Map::getCurrentSquare() {
	return currentSquare;
}

Chest* Map::getChestAtPosition(int x, int y){
	for (int i = 0; i < chests.size(); i++) {
		if (chests.at(i)->getPosition()[0] == x && chests.at(i)->getPosition()[1] == y) {
			return chests.at(i);
		}
		else {
			std::cout << "COULD NOT FIND CHEST AT "<< x << " " << y << "\n";
			return new Chest(this, 0, 0);
		}
	}

}
std::vector<Chest*> Map::getChests(){
	return chests;
}
Character* Map::getCharacter() {
	return character;
}

//! OBSERVER METHODS

void Map::attach(Observer* obs) {
	listeners.push_back(obs);
}
void Map::notify() {
	for each (Observer* obs in listeners)
	{
		obs->update();
	}
}
