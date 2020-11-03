#include "PhoneList.h"

#include <iostream>
#include <stdexcept>

Model::PhoneList::PhoneList()
{
	phoneList = new MySingleLinkedListImpl<Person>();
}

Model::PhoneList::~PhoneList()
{
	phoneList->~MySingleLinkedListImpl();
	delete phoneList;
}

void Model::PhoneList::AddPerson(Entity::Person person)
{
	phoneList->Add(person);
}

string Model::PhoneList::FindPhoneNumberByName(string name) const
{	
	if (name.empty())
	{
		throw invalid_argument("Invalid atgument!");
	}

	try
	{
		for (int i = 0; i < phoneList->GetSize(); i++)
		{
			if (phoneList->GetOnIndex(i).GetName() == name)
			{
				return phoneList->GetOnIndex(i).GetPhoneNumber();
			}
		}
	}
	catch (exception e)
	{
		cerr << e.what() << endl;
	}	
}

string Model::PhoneList::FindPhoneNumberById(int id) const
{
	if (id <= 0)
	{
		throw invalid_argument("Invalid atgument!");
	}

	try
	{
		for (int i = 0; i < phoneList->GetSize(); i++)
		{
			if (phoneList->GetOnIndex(i).GetId() == id)
			{
				return phoneList->GetOnIndex(i).GetPhoneNumber();
			}
		}
	}
	catch (exception e)
	{
		cerr << e.what() << endl;
	}

	throw invalid_argument("Person with given id doesn't exist!");
}
