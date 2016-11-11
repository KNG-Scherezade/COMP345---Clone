#pragma once

#include "Helmet.h"
#include "Armor.h"
#include "Belt.h"
#include "Ring.h"
#include "Shield.h"
#include "Weapon.h"
#include "Boots.h"
#include <vector>

class Character
{
public:
	Character();
	Character(int levelVal);
	~Character();

	void create();
	static int getModifier(int stat);
	void generateRandomStats();
	void calculateHp();
	void calculateAc();
	void calculateBaseAttackBonus();
	void calculateDamageBonus();
	void levelUp();
	bool validateNewCharacter();
	void hit(int damage);
	void printInventory();
	void printEquipped();
	void equip(int pos);
	void unequip(int slot);
	virtual std::string getType() { return ""; }
	void addToInventory(Item* item);

	//! Set the name of the character
	//! @param aName	Name of character
	void setName(std::string aName) { name = aName; }

	//! Get the name of the character
	//! @return	Name of the character
	std::string getName() { return name; }

	//! Set the level of the character
	//! @param levelVal	Level of the character
	void setLevel(int levelVal) { level = levelVal; }

	//! Get the level of the character
	//! @return	Level of the character
	int getLevel() { return level; }

	//! Set the strength attribute of the character
	//! @param strVal	Strength value
	void setStr(int strVal) { str = strVal; }

	//! Gets the strength attribute of the character
	//! @return Strength value
	int getStr() { return str; }

	//! Set the dexterity attribute of the character
	//! @param dexVal	Dexterity value
	void setDex(int dexVal) { dex = dexVal; }

	//! Get the dexterity attribute of the character
	//! @return Dexterity value
	int getDex() { return dex; }

	//! Set the constitution attribute of the character
	//! @param conVal	Constitution value
	void setCon(int conVal) { con = conVal; }

	//! Get the constitution attribute of the character
	//! @return Constitution value
	int Character::getCon() { return con; }

	//! Set the intelligence attribute of the character
	//! @param intelVal	Intelligence value
	void Character::setIntel(int intelVal) { intel = intelVal; }

	//! Get the intelligence attribute of the character
	//! @return Intelligence value
	int Character::getIntel() { return intel; }

	//! Set the wisdom attribute of the character
	//! @param wisVal	Wisdom value
	void Character::setWis(int wisVal) { wis = wisVal; }

	//! Get the wisdom attribute of the character
	//! @return Wisdom value
	int Character::getWis() { return wis; }

	//! Set the charisma attribute of the character
	//! @param Charisma value
	void Character::setCha(int chaVal) { cha = chaVal; }

	//! Get the charisma attirbute of the character
	//! @return Charisma value
	int Character::getCha() { return cha; }

	//! Set the strength modifier of the character
	//! @param str_modVal	Strength modifier
	void Character::setStr_mod(int str_modVal) { str_mod = str_modVal; }

	//! Get the strength modifier of the character
	//! @return Strength modifier
	int Character::getStr_mod() { return str_mod; }

	//! Set the dexterity modifier of the character
	//! @param dex_modVal	Dexterity modifier
	void Character::setDex_mod(int dex_modVal) { dex_mod = dex_modVal; }

	//! Get the dexterity modifier of the character
	//! @return Dexterity modifier
	int Character::getDex_mod() { return dex_mod; }

	//! Set the constitution modifier of the character
	//! @param con_modVal	Constitution modifier
	void Character::setCon_mod(int con_modVal) { con_mod = con_modVal; }

	//! Get the constitution modifier of the character
	//! @return Constitution modifier
	int Character::getCon_mod() { return con_mod; }

	//! Set the intelligence modifier of the character
	//! @param intel_modVal	Intelligence modifier
	void Character::setIntel_mod(int intel_modVal) { intel_mod = intel_modVal; }

	//! Get the intelligence modifier of the character
	//! @return Intelligence modifier
	int Character::getIntel_mod() { return intel_mod; }

	//! Set the wisdom modifier of the character
	//! @param wi_modVal	Wisdom modifier
	void Character::setWis_mod(int wis_modVal) { wis_mod = wis_modVal; }

	//! Get the wisdom modifier of the character
	//! @return Wisdom modifier
	int Character::getWis_mod() { return wis_mod; }

	//! Set the charisma 
	//! @param cha_modVal	Charisma modifier
	void Character::setCha_mod(int cha_modVal) { cha_mod = cha_modVal; }

	//! Get the charisma modifier of the character
	//! @return Charisma modifier
	int Character::getCha_mod() { return cha_mod; }

	//! Set the hitpoints of the character
	//! @param hpVal	Hitpoints
	void Character::setHp(int hpVal) { hp = hpVal; }

	//! Get the hitpoints of the character
	//! @return Hitpoints
	int Character::getHp() { return hp; }

	//! Set the maximum hitpoints (full hp) of the character (will avoid over healing later)
	//! @param maxHpVal	Character's full hitpoints
	void Character::setMaxHp(int maxHpVal) { maxHp = maxHpVal; }

	//! Get the maximum hitpoints of the character
	//! @return The maximum amount of hitpoints the character currently has
	int Character::getMaxHp() { return maxHp; }

	//! Set the armor class of the character
	//! @param acVal	Armor class
	void Character::setAc(int acVal) { ac = acVal; }

	//! Get the armor class of the character
	//! @return Armor class
	int Character::getAc() { return ac; }

	//! Set the attack bonus of the character
	//! @param attackBonusVal	Attack bonus
	void Character::setAttackBonus(int attackBonusVal) { attackBonus = attackBonusVal; }

	//! Get the attack bonus of the character
	//! @return Attack bonus
	int Character::getAttackBonus() { return attackBonus; }

	//! Set the damage bonus of the character
	//! @param damageBonusVal	Damage bonus
	void Character::setDamageBonus(int damageBonusVal) { damageBonus = damageBonusVal; }

	//! Get the damage bonus of the character
	//! @return Damage bonus
	int Character::getDamageBonus() { return damageBonus; }

	//! Set the inventory of the character
	//! @param inv	Vector of items in inventory
	void setInventory(vector<Item*> inv) { inventory = inv; }

	//! Get the inventory of tha character
	//! @return Vector of inventory items
	vector<Item*> getInventory() { return inventory; }

	//! Set the helmet worn by the character
	//! @param aHelmet	Helmet
	void setHelmet(Helmet* aHelmet) { helmet = aHelmet; }

	//! Get the helmet being worn by the character
	//! @return Helmet  worn
	Helmet* getHelmet() { return helmet; }

	//! Set the armor worn by the character
	//! @param newArmor	Armor
	void setArmor(Armor* newArmor) { armor = newArmor; }

	//! Get the armor being worn by the character
	//! @return Armor  worn
	Armor* getArmor() { return armor; }

	//! Set the shield worn by the character
	//! @param aShield	Shield
	void setShield(Shield* aShield) { shield = aShield; }

	//! Get the shield being worn by the character
	//! @return Shield  worn
	Shield* getShield() { return shield; }

	//! Set the ring worn by the character
	//! @param aRing	Ring
	void setRing(Ring* aRing) { ring = aRing; }

	//! Get the ring being worn by the character
	//! @return Ring  worn
	Ring* getRing() { return ring; }

	//! Set the belt worn by the character
	//! @param aBelt	Belt
	void setBelt(Belt* aBelt) { belt = aBelt; }

	//! Get the belt being worn by the character
	//! @return Belt  worn
	Belt* getBelt() { return belt; }

	//! Set the boots worn by the character
	//! @param newBoots	Boots
	void setBoots(Boots* newBoots) { boots = newBoots; }

	//! Get the boots being worn by the character
	//! @return Boots  worn
	Boots* getBoots() { return boots; }

	//! Set the weapon wielded by the character
	//! @param aWeapon	Weapon
	void setWeapon(Weapon* aWeapon) { weapon = aWeapon; }

	//! Get the weapon being wielded by the character
	//! @return Weapon  wielded
	Weapon* getWeapon() { return weapon; }


private:
	std::string name;
	int level;
	int str;
	int dex;
	int con;
	int intel;
	int wis;
	int cha;
	int str_mod;
	int dex_mod;
	int con_mod;
	int intel_mod;
	int wis_mod;
	int cha_mod;
	int hp;
	int maxHp;
	int ac;
	int attackBonus;
	int damageBonus;
	vector<Item*> inventory;
	Helmet* helmet;
	Armor* armor;
	Shield* shield;
	Ring* ring;
	Belt* belt;
	Boots* boots;
	Weapon* weapon;
};

