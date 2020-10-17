#include "Object.h"

Object::Object()
{
}

Object::Object(int id)
{
	this->id = id;
	this->x = 0;
	this->y = 0;
}

Object::~Object()
{
}

void Object::SetX(double x)
{
	this->x = x;
}

void Object::SetY(double y)
{
	this->y = y;
}

int Object::GetId() const
{
	return id;
}

double Object::GetX() const
{
	return x;
}

double Object::GetY() const
{
	return y;
}
