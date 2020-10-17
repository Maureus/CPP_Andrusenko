#pragma once
#include "Object.h"

class MovableObject :
    public Object
{
    double directionAngle;
public:
    MovableObject(int);
    virtual void SetDirectionAngle(double);
    virtual double GetDirectionAngle() const;
};

