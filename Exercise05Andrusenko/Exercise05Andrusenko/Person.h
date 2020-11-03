#pragma once

#include <string>

static int counter = 1;

namespace Entity {
	class Person
	{
		int id;
		std::string name;
		std::string phoneNumber;		
	public:
		Person(const std::string& name, const std::string& phoneNumber);		
		int GetId() const;
		std::string GetName() const;
		std::string GetPhoneNumber() const;
	};
}