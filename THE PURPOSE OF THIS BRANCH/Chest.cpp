#include "Chest.h"

Chest::Chest(Map* map, int x, int y)
{
	chestState = map->getCharacterLevel();
	this->map = map;
	position[0] = x;
	position[1] = y;
}


Chest::~Chest()
{
}


//updates the chestState which is a reflection of the characters level
void Chest::updateChestState() {
	chestState = map->getCharacterLevel();
}

//! sets check for if chest is closed or not
void Chest::setOpen(bool flag) {
	open = flag;
}

//! gets the chestState which is a reflection of the characters level
int Chest::getChestState() {
	return chestState;
}

//! gets check for if chest is closed or not
bool Chest::getOpen() {
	return open;
}

//! gets chest position in x and y
int * Chest::getPosition() {
	return position;
}

//! generic observer functions done in super
void Chest::notify() {
	for each(Observer* obs in listeners) {
		obs->update();
	}
}
void Chest::attach(Observer* obs) {
	listeners.push_back(obs);
}

