#pragma once

#include <string>

#include "Person.h"
#include "MySinglyLinkedListImpl.h"

using namespace Entity;

namespace Model {
	class PhoneList
	{
		MySingleLinkedListImpl<Person> *phoneList;
	public:
		PhoneList();
		~PhoneList();
		void AddPerson(Entity::Person person);
		string FindPhoneNumberByName(std::string name) const;
		string FindPhoneNumberById(int id) const;
	};
}


