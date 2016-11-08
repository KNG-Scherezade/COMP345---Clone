//!@file ItemGenerator.h
//! @brief Class declaration of a random ItemGenerator
#pragma once
#include "Item.h"
//! Class declaration of a random ItemGenerator
class ItemGenerator
{
public:
	ItemGenerator();
	~ItemGenerator();
	Item generateItem(int level);
};

