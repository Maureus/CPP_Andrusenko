#pragma once
#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H


#include "Object.h"
#include "Obstacle.h"


class StaticObject :
    public Object
{
private:
    Obstacle obstacle;
public:
    
    StaticObject(int, Obstacle);
    Obstacle GetObstacle() const;    

};



#endif // !STATIC_OBJECT_H

