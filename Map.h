#pragma once
#include "Node.h"
#include "Character.h"
#include "ItemContainer.h"
#include "Observable.h"
#include "Monster.h"
#include "ChestObserver.h"

#include <vector>
using namespace std;

//! @file 
//! @brief		Class representing the map. Will most likely change in future versions
//!

//! Class representing the map.

//! Game rules:	This class allows for the creation of customs maps of variable size that will be determined
//!				prior to generation of the map. The map will be able to contain traversable empty cells, 
//!				untraversable walls, and cells that will be occupied by the character, enemies, chests, doors, 
//!				and possibly more. The class also allows to objects to be inserted into cells,
//!				to check if a certain cell contains an object, and to validate the map	by veryfing that it
//!				contains a start cell, and end cell, and that there is a path of empty cells between them.
//!		
//! Design:		No external libraries have been used. The map is a char matrix. Currently, the empty char ' '
//!				represents an empty space in the map, the char 'e' represents the end cell, and the char 's'
//!				represents the start cell, the char "|" represents a wall, the char "t" represents a chest,
//!				the char "m" represents a monster. At the moment, any other character will indicate that the cell is not
//!				traversable. In the future, enums may be implemented to force specific values into the map instead of
//!				stand alone characters.
class ItemContainer;
class Character;
class Monster;

class Map : public Subject
{
public:
	Map();
	Map(Map* copyMap);
	Map(int newRows, int newColumns);
	Map(int newRows, int newColumns, string newName);
	~Map();

	//! Searches for the start cell represented by te character 's'. 
	//!
	//! @return	Node pointer representing the start cell, if found. 
	//!			Else, returns an empty pointer.
	Node* findStart();

	//! Searches for the end cell represented by te character 'e'. 
	//!
	//! @return	Node pointer representing the end cell, if found. 
	//!			Else, returns an empty pointer.
	Node* findEnd();

	//! General method for validating the path. First calls a methods that verifiy that the map has a start
	//! and an end (findStart and findEnd). Then calls another method to check if a valid path exists
	//! within the map (findValidPath).
	//!
	//! @return	bool indicating whether or not the map has a valid path the start and end cells.
	bool validatePath();

	//! Fills the specified cell with a char representing an object.
	//! The isOccupied function should be called in the controller, before calling this function, 
	//! to make sure that the cell is empty.
	//!
	//! @param	row		Row where the char will be inserted.
	//!	@param	column	Column where the char will be inserted.
	//! @param	obj		Character that will be inserted.
	void fillCell(int row, int column, string obj);

	//! Returns a bool value indicating whether or not the specified cell is occcupied.
	//!
	//! @param	row		Row that needs to be checked.
	//! @param	column	Column that needs to be checked.	
	//!
	//! @return			bool indicating whether or not the specified cell is occupied.
	bool isOccupied(int row, int column);

	//! Prints the map with its contents.
	void printMap();

	//! Sets the map's name
	//! @param	newName		New name to set for the map.
	void setMapName(string newName);

	//! Returns the number of rows in the map.
	//!	@return	the number of rows in the map
	int getRows();

	//! Returns the number of columns in the map.
	//!	@return	the number of columns in the map
	int getColumns();
	
	//! Returns the map name.
	//!	@return	the map name.
	string getMapName();

	//! Returns the cha saved at a position in the map.
	//!
	//! @param	row		Row that needs to be checked.
	//! @param	column	Column that needs to be checked.	
	//!
	//! @return	char in the row and column sent as parameters
	char getCharObject(int row, int column);

	//! Returns the string saved at a position in the map.
	//!
	//! @param	row		Row that needs to be checked.
	//! @param	column	Column that needs to be checked.	
	//!
	//! @return	string in the row and column sent as parameters
	string get(int row, int column);

	bool isFunctionallyOccupied(int col, int row);	
	void createMoveSpaceVector(std::vector <std::vector<int>>* validSpaces, int initialPosition[], int moveRate);
	int checkStandingSpace(int col, int row);

	void setCurrentSquare(int clearState);
	void setCharacterPosition(int pos[]);
	void setCharacter(Character *chara);

	vector<vector<std::string>> getMap();
	vector<vector<std::string>>* getMapReference();

	Character* getCharacter();
	int* getCharacterPosition();
	int getCharacterLevel();
	int getCurrentSquare();

	std::vector<Monster*> getMonsters() { return monsters; }

	void addChest(ItemContainer* ic);
	std::vector<ItemContainer*> getChests();
	ItemContainer* getChestAtPosition(int x, int y);
	Monster* getMonstersAtPosition(int x, int y);
	void removeMonster(Monster* mon);
	//Subject inheritence / observer methods
	void attach(Observer* obs);
	void notify();

	//! Allocates memory for the map and sets the cell to empty values.
	//! Empty cells are represented by an empty space character (' ').
	void initializeMap();
	bool characterInitialized = false;


	//! Calculates the id for a Node. The id of a Node is it's linear position in the map.
	//! In other words, it's the x-th cell the map.
	//!
	//! @param		row		The row the Node is located on.
	//!	@param		column	The column the Node is located on.
	//!
	//!	@return		The node's id.
	int calculateNodeId(int row, int column);

	//! Calculates the heuristic for a Node. The heuristic is the number of cells 
	//! the Node is away from the end cell.
	//!
	//! @param		row			The row the Node is located on.
	//!	@param		column		The column the Node is located on.
	//!	@param		endRow		The row the end cell is located on.
	//!	@param		endColumn	The column the end cell is located on.
	//!
	//!	@return		The Node's heuristic value. The heuristic is the number of cells 
	//!				the Node is away from the end cell.
	int calculateHeuristic(int row, int column, int endRow, int endColumn);
private:

	int characterPosition[2];
	Character* character;
	int currentSquare;

	std::vector<ItemContainer*> chests;

	std::vector<Monster*> monsters;
	//! Number of rows in the map.
	int rows;

	//! Number of columns in the map.
	int columns;

	//! Char representation of the map.
	//char **map;

	//! Used as filename when saving maps. If maps have the same name, the file will be overwritten.
	vector<vector<std::string>> map;

	//! name of map
	string mapName;

	//! Dealocates memory for the map.
	void deleteMap();

	//! Searches for a valid path within the map. Returns a bool value indicating whether or not
	//! a valid path exists between the start and end cells. Personal implementation of the a* algorithm.
	//! Does not currently take keys and doors into account.
	//! 
	//! @param	startPointer	Pointer to the Node representing the start cell.
	//! @param	endPointer		Pointer to the Node representing the end cell.
	//!
	//! @return	bool value indicating whether or not a valid path exists between the start and end cells.
	bool findValidPath(Node* startPointer, Node* endPointer);


};

