#pragma once
#include "Character.h"
#include <string>

class Fighter : public Character
{
public:
	Fighter();
	Fighter(int levelVal, Map* map);
	Fighter(int levelVal);
	~Fighter();
	std::string getType() { return "Fighter"; }
};
