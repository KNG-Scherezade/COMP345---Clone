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
	string getName() { return name; };
	void setName(string i_name) { name = i_name; };

private:

 
protected:	
	string name;
	int str;
	int dex;
	int wis;
	int constitution;
	int charisma;
	int ac;
	int level;
	int atk;
	int dmg;
};

