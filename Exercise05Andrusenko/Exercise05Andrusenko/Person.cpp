#include "Person.h"
#include <stdexcept>

using namespace std;


Entity::Person::Person(const string& name, const string& phoneNumber)
{		
	this->id = counter++;
	this->name = name;
	this->phoneNumber = phoneNumber;
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
