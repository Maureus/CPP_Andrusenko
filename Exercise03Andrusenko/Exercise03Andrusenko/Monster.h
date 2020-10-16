#pragma once
#include "MovableObject.h"
class Monster :
    public MovableObject
{
    int hp;
    int maxhp;
public:
    Monster(int);
    void SetHp(int);
    void SetMaxhp(int);
    int GetHp() const;
    int GetMaxhp() const;
};

