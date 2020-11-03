#include "Person.h"
#include <stdexcept>

using namespace std;

Entity::Person::Person(int id, const string& name, const string& phoneNumber)
{	
	if (id <= 0)
	{
		throw invalid_argument("Id is negatie or equals to 0!");
	}
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
