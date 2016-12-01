#pragma once
#include "AbstractStrategy.h"
#include "GenericMapItem.h"


class AggressorStrategy :
	public AbstractStrategy
{
public:
	AggressorStrategy();
	~AggressorStrategy();

	int decideAction(GenericMapItem* chara);
	void attack(GenericMapItem* chara);
	void move(GenericMapItem* chara);
	int interact(GenericMapItem* chara);
};

