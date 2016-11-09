//! Nodes are documented in Akash's design.
//! They hold information on a certain point in the map.

#pragma once

class Node
{
public:
	Node();
	Node(int newId, int newRow, int newColumn);
	Node(int newId, int newRow, int newColumn, int newHeuristic, bool newTraversable);
	void setHeuristic(int newHeuristic);
	void setId(int newId);
	void setRow(int newRow);
	void setColumn(int newColumn);
	void setTraversable(bool newTraversable);
	int getHeuristic();
	int getId();
	int getRow();
	int getColumn();
	bool getTraversable();

private:
	int heuristic;
	int id;
	int row;
	int column;
	bool traversable;
};

