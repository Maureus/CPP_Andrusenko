#pragma once
#include "Object.h"

class MovableObject :
    public Object
{
    double rotationAngle;
public:
    MovableObject(int);
    void SetRotationAngle(double);
    double GetRotationAngle() const;
};

