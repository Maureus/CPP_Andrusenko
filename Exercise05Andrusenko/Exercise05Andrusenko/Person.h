#pragma once
#include <string>


namespace Entity {
	class Person
	{
		int id;
		std::string name;
		std::string phoneNumber;
	public:
		Person(int id, std::string name, std::string phoneNumber);
		~Person();
		int GetId() const;
		std::string GetName() const;
		std::string GetPhoneNumber() const;
	};
}


