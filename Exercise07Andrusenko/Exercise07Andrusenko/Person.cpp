#include "Person.h"
#include <stdexcept>

using namespace std;

Person::Person()
{
}

Person::Person(const string& firstname, const string& lastname,const Address& lta, const Date& dob)
{
	if (firstname.empty() && lastname.empty())
	{
		throw invalid_argument("Unaceptable person!");
	}

	this->fristname = firstname;
	this->lastname = lastname;
	this->longTermAddress = lta;
	this->dateOfBirth = dob;
}

Person::~Person()
{
}

std::ostream& operator<<(std::ostream& os, const Person& person)
{
	os << person.fristname << " " << person.lastname << " " << person.longTermAddress << " " << person.dateOfBirth;
	return os;
}

std::istream& operator>>(std::istream& is, Person& person)
{		
	is >> person.fristname >> person.lastname >> person.longTermAddress >> person.dateOfBirth;
	return is;
}
