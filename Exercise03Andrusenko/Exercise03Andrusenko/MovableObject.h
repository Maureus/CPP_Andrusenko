#ifndef MOVABLE_OBJECT_H
#define MOVABLE_OBJECT_H

#include "Object.h"

class MovableObject :
    public Object
{
    double directionAngle;
public:
    MovableObject(int);
    void SetDirectionAngle(double);
    double GetDirectionAngle() const;
};

#endif // !MOVABLE_OBJECT_H