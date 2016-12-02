//!@file Item.h
//!  @brief Declaration of an Item
//!
//!  This class represents an item 
//!  Contains stats that d20 items may have, but does not make them accessible. 
#pragma once
#include <string>
using namespace std;

//! This class represents an item 
class Item
{
public:
	Item();
	~Item();
	virtual string getName() { return name; };
	void setName(string i_name) { name = i_name; };
	string getType() { return type; };
	
	string toString();
	void setLevel(int lvl) { level = lvl; }

private:

 
protected:	
	string name;
	int str;
	int dex;
	int wis;
	int constitution;
	int charisma;
	int intel;
	int ac;
	int level;
	int atk;
	int dmg;
	string type;
};

