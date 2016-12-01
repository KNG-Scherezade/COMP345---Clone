#include "AggressorStrategy.h"
#include "Monster.h"

#define CHARA_POSITION_X ((Monster*) chara)->position[1]//cols are x
#define CHARA_POSITION_Y ((Monster*) chara)->position[0]//rows are y


#define MONSTER ((Monster*) chara)
#define MAP ((Monster*) chara)->getMap()
#define PLAYER	((Monster*)chara)->getMap()->getCharacterPosition()

AggressorStrategy::AggressorStrategy()
{

}


AggressorStrategy::~AggressorStrategy()
{
}
int AggressorStrategy::decideAction(GenericMapItem* chara){
	MONSTER->createPathToCharacter(
		new Node(MAP->calculateNodeId(MONSTER->position[1], MONSTER->position[0]), MONSTER->position[1], MONSTER->position[0]), //Monster local
		new Node(MAP->calculateNodeId(PLAYER[0], PLAYER[1]), PLAYER[0], PLAYER[1])); //Player local

	if (((Monster*)chara)->pathToCharacter.size() == 1)
		attack(chara);
	else
		move(chara);

	return 0;
}

void AggressorStrategy::attack(GenericMapItem* chara){
	std::cout << "It Attacks\n";
}

int AggressorStrategy::interact(GenericMapItem* chara){
	return 0;
}
void AggressorStrategy::move(GenericMapItem* chara){
	((Monster*)chara)->position[0] = ((Monster*)chara)->pathToCharacter.at(1).at(0); //0 x 
	((Monster*)chara)->position[1] = ((Monster*)chara)->pathToCharacter.at(1).at(1);// 1 y
	MONSTER->pathToCharacter.clear();
}