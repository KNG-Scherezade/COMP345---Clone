#include "Monster.h"
//!@file Monster.cpp
//!  @brief Implementation of DnD monster class
//!
//!  This class is a monster that the character will combat
//!  It contains all basic stats that a monster has in D20

//! Default constructor sets attributes to level 1
Monster::Monster()
{
	hitpoints = 1;
	attack = 1;
	level = 1;
	dex = 1;
	str = 1; 
	con = 1;
	intel = 1;
	wis = 1;
	cha = 1;
}

//! Constructor assigns stats based on level
//! @param m_level sets stats based on this level
Monster::Monster(int m_level)
{
	levelUpStats(m_level);
}

Monster::~Monster()
{
}

//! Assigns stats based on level
//! @param m_level sets stats based on this level
void Monster::levelUpStats(int m_level)
{
	hitpoints = m_level;
	attack = m_level;
	level = m_level;
	dex = m_level;
	str = m_level;
	con = m_level;
	intel = m_level;
	wis = m_level;
	cha = m_level;
}
