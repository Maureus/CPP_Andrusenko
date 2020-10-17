#include "MovableObject.h"

MovableObject::MovableObject(int id) : Object(id)
{	
}

void MovableObject::SetDirectionAngle(double rotationAngle)
{
	this->directionAngle = rotationAngle;
}

double MovableObject::GetDirectionAngle() const
{
	return directionAngle;
}
