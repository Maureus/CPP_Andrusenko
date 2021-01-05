#include "Student.h"
#include <stdexcept>

Student::Student(ObjectValue* object)
{
	DynamicArray<KeyValuePair>* temp = object->getValues();
	for (int i = 0; i < temp->getSize(); i++)
	{
		if (temp->getElementAt(i).getKey() == "id")
		{
			NumberValue* nV;
			if (nV = dynamic_cast<NumberValue*>(temp->getElementAt(i).getValue()))
			{
				this->id = nV->get();
			}
			else
			{
				throw std::invalid_argument("Argument type missmatch: id.");
			}
		}
		else if (temp->getElementAt(i).getKey() == "firstname")
		{
			StringValue* sV;
			if (sV = dynamic_cast<StringValue*>(temp->getElementAt(i).getValue()))
			{
				this->firstname = sV->get();
			}
			else
			{
				throw std::invalid_argument("Argument type missmatch: firstname.");
			}
		}
		else if (temp->getElementAt(i).getKey() == "lastname")
		{
			StringValue* sV;
			if (sV = dynamic_cast<StringValue*>(temp->getElementAt(i).getValue()))
			{
				this->lastname = sV->get();
			}
			else
			{
				throw std::invalid_argument("Argument type missmatch: lastname.");
			}
		}
		else if (temp->getElementAt(i).getKey() == "gender")
		{
			StringValue* sV;
			if (sV = dynamic_cast<StringValue*>(temp->getElementAt(i).getValue()))
			{
				this->gender = sV->get();
			}
			else
			{
				throw std::invalid_argument("Argument type missmatch: gender.");
			}
		}
		else if (temp->getElementAt(i).getKey() == "dateofbirth")
		{
			ObjectValue* oV;
			if (oV = dynamic_cast<ObjectValue*>(temp->getElementAt(i).getValue()))
			{
				Date dob{ oV };
				this->dateofbirth = dob;
			}
			else
			{
				throw std::invalid_argument("Argument type missmatch: dateofbirth.");
			}
		}
		else if (temp->getElementAt(i).getKey() == "assigned_subjects")
		{
			ArrayValue* aV;
			if (aV = dynamic_cast<ArrayValue*>(temp->getElementAt(i).getValue()))
			{
				DynamicArray<Value*>* arrayValues = aV->getValues();
				for (int i = 0; i < arrayValues->getSize(); i++)
				{
					subjects.append(dynamic_cast<NumberValue*>(arrayValues->getElementAt(i))->get());
				}
			}
			else
			{
				throw std::invalid_argument("Argument type missmatch: assigned_subjects.");
			}
		}
	}
}

Student::Student(int id, std::string firstname, std::string lastname, std::string gender, Date dateofbirth)
{
	if (id < 1 || firstname.empty() || lastname.empty() || gender.empty())
	{
		throw std::invalid_argument("Invalid arguments for Student.");
	}

	this->id = id;
	this->firstname = firstname;
	this->lastname = lastname;
	this->gender = gender;
	this->dateofbirth = dateofbirth;
}

void Student::AddSubjectId(int id)
{
	if (id < 1)
	{
		throw std::invalid_argument("Id must be bigger than 0.");
	}

	for (int i = 0; i < subjects.getSize(); i++)
	{
		if (subjects.getElementAt(i) == id)
		{
			throw std::invalid_argument("Student already has a subject with given id.");
		}
	}

	subjects.append(id);
}

void Student::DeleteSubjectId(int id)
{
	for (int i = 0; i < subjects.getSize(); i++)
	{
		if (subjects.getElementAt(i) == id)
		{
			subjects.deleteAtIndex(i);
			return;
		}
	}
}

ObjectValue* Student::deserialize() const
{
	ObjectValue* newSt = new ObjectValue;
	newSt->append(KeyValuePair("id", new NumberValue(id)));
	newSt->append(KeyValuePair("firstname", new StringValue(firstname)));
	newSt->append(KeyValuePair("lastname", new StringValue(lastname)));
	newSt->append(KeyValuePair("gender", new StringValue(gender)));
	newSt->append(KeyValuePair("dateofbirth", dateofbirth.createObject()));
	ArrayValue* newArr = new ArrayValue;
	for (int i = 0; i < subjects.getSize(); i++)
	{
		newArr->append(new NumberValue(subjects.getElementAt(i)));
	}
	newSt->append(KeyValuePair("assigned_subjects", newArr));
	return newSt;
}

int Student::getId() const
{
	return id;
}

void Student::setFirstname(std::string firstname)
{
	if (firstname.empty())
	{
		throw invalid_argument("String is empty.");
	}

	this->firstname = firstname;
}

void Student::setLastname(std::string lastname)
{
	if (lastname.empty())
	{
		throw invalid_argument("String is empty.");
	}

	this->lastname = lastname;
}

void Student::setGender(std::string gender)
{
	if (gender.empty())
	{
		throw invalid_argument("String is empty.");
	}

	this->gender = gender;
}

void Student::setDateOfBirth(Date dob)
{
	this->dateofbirth = dob;
}