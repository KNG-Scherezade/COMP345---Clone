#include "FriendlyStrategy.h"
#include "Monster.h"
#include "Node.h"

#include "Attack.h"

#define CHARA_POSITION_X ((Monster*) chara)->position[1]//cols are x
#define CHARA_POSITION_Y ((Monster*) chara)->position[0]//rows are y


#define MONSTER ((Monster*) chara)
#define MAP ((Monster*) chara)->getMap()
#define PLAYER	((Monster*)chara)->getMap()->getCharacterPosition()

FriendlyStrategy::FriendlyStrategy()
{

}


FriendlyStrategy::~FriendlyStrategy()
{
}
int FriendlyStrategy::decideAction(GenericMapItem* chara){
	MONSTER->createPathToCharacter(
		new Node(MAP->calculateNodeId(MONSTER->position[1], MONSTER->position[0]), MONSTER->position[1], MONSTER->position[0]), //Monster local
		new Node(MAP->calculateNodeId(PLAYER[0], PLAYER[1]), PLAYER[0], PLAYER[1])); //Player local

	if (((Monster*)chara)->pathToCharacter.size() == 0)
		attack(chara);
	else
		move(chara);

	MONSTER->pathToCharacter.clear();
	return 0;
}

void FriendlyStrategy::attack(GenericMapItem* chara){
	if (!MONSTER->attacked)
		std::cout << "It doesn't Attack\n";
	else {
		std::cout << "It attacked in vengence\n";
		Attack atk;
		std::cout << atk.makeAttack(MONSTER, ((Monster*)chara)->getMap()->getCharacter());
	}
}

int FriendlyStrategy::interact(GenericMapItem* chara){
	return 0;
}
void FriendlyStrategy::move(GenericMapItem* chara){
	((Monster*)chara)->position[0] = ((Monster*)chara)->pathToCharacter.at(0).at(0); //0 x 
	((Monster*)chara)->position[1] = ((Monster*)chara)->pathToCharacter.at(0).at(1);// 1 y

}