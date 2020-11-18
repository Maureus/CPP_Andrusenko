#pragma once
#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include "Address.h"
#include "Date.h"

class Person
{
	std::string fristname;
	std::string lastname;
	Address longTermAddress;
	Date dateOfBirth;
public:
	Person();
	Person(const std::string& firstname, const std::string& lastname, const Address& lta, const Date& dob);
	~Person();
	friend std::ostream& operator<<(std::ostream& os, const Person& person);
	friend std::istream& operator>>(std::istream& is, Person& person);
};

#endif // !PERSON_H



