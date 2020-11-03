#include "PhoneList.h"

#include <iostream>
#include <stdexcept>

using namespace std;
using namespace Entity;

Model::PhoneList::PhoneList()
{
	phoneList = new MySingleLinkedListImpl<Entity::Person>();
}

Model::PhoneList::~PhoneList()
{
	phoneList->~MySingleLinkedListImpl();
	delete phoneList;
}

void Model::PhoneList::AddPerson(Entity::Person person)
{
	for (int i = 0; i < phoneList->GetSize(); i++)
	{
		if (phoneList->GetOnIndex(i).GetName() == person.GetName())
		{
			throw invalid_argument("Person with this name already exists!");
		}
	}
	phoneList->Add(person);
}

string Model::PhoneList::FindPhoneNumberByName(string name) const
{	
	if (name.empty())
	{
		throw invalid_argument("Name is empty!");
	}

	for (int i = 0; i < phoneList->GetSize(); i++)
	{
		if (phoneList->GetOnIndex(i).GetName() == name)
		{
			return phoneList->GetOnIndex(i).GetPhoneNumber();
		}
	}	

	throw invalid_argument("Person with given name doesn't exist!");
}

string Model::PhoneList::FindPhoneNumberById(int id) const
{
	if (id <= 0)
	{
		throw invalid_argument("Id is lower or equals to 0!");
	}
	
	for (int i = 0; i < phoneList->GetSize(); i++)
	{
		if (phoneList->GetOnIndex(i).GetId() == id)
		{
			return phoneList->GetOnIndex(i).GetPhoneNumber();
		}
	}		

	throw invalid_argument("Person with given id doesn't exist!");
}
