#pragma once
#include <string>

using namespace std;

namespace Entity {
	class Person
	{
		int id;
		string name;
		string phoneNumber;
	public:
		Person(int id, string name, string phoneNumber);
		~Person();
		int GetId() const;
		string GetName() const;		
		string GetPhoneNumber() const;
	};
}


