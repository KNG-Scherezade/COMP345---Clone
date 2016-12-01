#pragma once
#include "AbstractStrategy.h"
#include "GenericMapItem.h"
class FriendlyStrategy :
	public AbstractStrategy
{
public:
	FriendlyStrategy();
	~FriendlyStrategy();

	int decideAction(GenericMapItem* chara);
	void attack(GenericMapItem* chara);
	void move(GenericMapItem* chara);
	int interact(GenericMapItem* chara);
};

