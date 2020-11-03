#include "Person.h"

Entity::Person::Person(int id, std::string name, std::string phoneNumber)
{
	this->id = id;
	this->name = name;
	this->phoneNumber = phoneNumber;
}

Entity::Person::~Person()
{
}

int Entity::Person::GetId() const
{
	return id;
}

string Entity::Person::GetName() const
{
	return name;
}

string Entity::Person::GetPhoneNumber() const
{
	return phoneNumber;
}
