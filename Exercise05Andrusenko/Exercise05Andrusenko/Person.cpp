#include "Person.h"
#include <stdexcept>

using namespace std;

Entity::Person::Person(int id, std::string name, std::string phoneNumber)
{
	if (id <= 0)
	{
		throw invalid_argument("Negative or 0 id!");
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
