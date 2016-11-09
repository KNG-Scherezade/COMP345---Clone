#include "Node.h"

// Number of cells the node is away from the end cell of the map.
int heuristic;
int row;
int column;
int id;
bool traversable;

Node::Node()
{
	id = -1;
	heuristic = -1;
	row = -1;
	column = -1;
	traversable = false;
}

Node::Node(int newId, int newRow, int newColumn) : id(newId), row(newRow), column(newColumn)
{
	heuristic = -1;
	traversable = false;
}

Node::Node(int newId, int newRow, int newColumn, int newHeuristic, bool newTraversable) : id(newId), row(newRow), column(newColumn), heuristic(newHeuristic), traversable(newTraversable) { }

void Node::setHeuristic(int newHeuristic)
{
	heuristic = newHeuristic;
}

void Node::setId(int newId)
{
	id = newId;
}

void Node::setRow(int newRow)
{
	row = newRow;
}

void Node::setColumn(int newColumn)
{
	column = newColumn;
}

void Node::setTraversable(bool newTraversable)
{
	traversable = newTraversable;
}

int Node::getHeuristic()
{
	return heuristic;
}

int Node::getId()
{
	return id;
}

int Node::getRow()
{
	return row;
}

int Node::getColumn()
{
	return column;
}

bool Node::getTraversable()
{
	return traversable;
}
