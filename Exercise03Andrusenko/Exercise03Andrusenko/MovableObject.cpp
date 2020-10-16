#include "MovableObject.h"

MovableObject::MovableObject(int id) : Object(id)
{	
}

void MovableObject::SetRotationAngle(double rotationAngle)
{
	this->rotationAngle = rotationAngle;
}

double MovableObject::GetRotationAngle() const
{
	return rotationAngle;
}
