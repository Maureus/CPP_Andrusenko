#pragma once

#include <string>

#include "Person.h"
#include "MySinglyLinkedListImpl.h"



namespace Model {
	class PhoneList
	{
		MySingleLinkedListImpl<Entity::Person> *phoneList;
	public:
		PhoneList();
		~PhoneList();
		void AddPerson(Entity::Person person);
		std::string FindPhoneNumberByName(std::string name) const;
		std::string FindPhoneNumberById(int id) const;
	};
}


