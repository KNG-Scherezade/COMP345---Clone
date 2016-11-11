#pragma once

//! @file Node.h
//! @brief	Class representing a cell in the map. 
//!

//! Class representing a cell in the map

//! Will most likely change in a
//!	future version. This class was implemented in order to facilitate 
//!	the pathfinding algorithm in the findValidPath function in the Map class.
class Node
{
public:
	Node();
	Node(int newId, int newRow, int newColumn);
	Node(int newId, int newRow, int newColumn, int newHeuristic, bool newTraversable);

	//! Sets the Node's heuristic value.
	//! @param	newHeuristic	The new heuristic value to set.
	void setHeuristic(int newHeuristic);

	//! Sets the Node's id.
	//! @param	newId	The new id value to set.
	void setId(int newId);

	//! Sets the Node's row.
	//! @param	newRow	The new row value to set.
	void setRow(int newRow);

	//! Sets the Nodes's column.
	//! @param	newColumn	The new column value to set.
	void setColumn(int newColumn);

	//! Sets the Node's bool traversable.
	//! @param	newTraversable	The new traversable value to set.
	void setTraversable(bool newTraversable);

	//! @return The Node's heuristic.
	int getHeuristic();

	//! @return The Node's id.
	int getId();

	//! @return The Node's row.
	int getRow();

	//! @return The Node's column.
	int getColumn();

	//! @return The Node's traversable field.
	bool getTraversable();

private:
	//! The heuristic is the number of cells the Node is away from the end cell. If it is right next
	//! to the end cell, the value will be 1.
	int heuristic;

	//! The id of a Node is its linear position in the map. In other words, it's the x-th cell the map. 0 based.
	int id;

	//! The row the Node is located on.
	int row;

	//! The column the node is located on.
	int column;

	//! bool indicating whether or not the Node can be traversed.
	bool traversable;
};
