#pragma once
#include "AbstractStrategy.h"
#include "GenericMapItem.h"

class HumanPlayerStrategy :
	public AbstractStrategy
{
public:
	HumanPlayerStrategy();
	~HumanPlayerStrategy();
	int decideAction(GenericMapItem* chara);
	void attack(GenericMapItem* chara);
	void move(GenericMapItem* chara);
	int interact(GenericMapItem* chara);
};

