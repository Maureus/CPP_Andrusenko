#include "StaticObject.h"

StaticObject::StaticObject(int id, Obstacle obstacle) : Object(id)
{		
	this->obstacle = obstacle;
}

Obstacle StaticObject::GetObstacle() const
{
	return obstacle;
}



