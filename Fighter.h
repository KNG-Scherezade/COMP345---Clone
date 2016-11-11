#pragma once
#include "Character.h"
#include <string>

class Fighter : public Character
{
public:
	Fighter();
	Fighter(int level);
	~Fighter();
	std::string getType() { return "Fighter"; }
};

