#include "Monster.h"

Monster::Monster(int id) : MovableObject(id)
{
}

void Monster::SetHp(int hp)
{
	this->hp = hp;
}

void Monster::SetMaxhp(int maxhp)
{
	this->maxhp = maxhp;
}

int Monster::GetHp() const
{
	return hp;
}

int Monster::GetMaxhp() const
{
	return maxhp;
}
