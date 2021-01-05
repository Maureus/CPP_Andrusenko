#include "Subject.h"
#include <stdexcept>

Subject::Subject(ObjectValue* object)
{
	DynamicArray<KeyValuePair>* objectValues = object->getValues();
	for (int i = 0; i < objectValues->getSize(); i++)
	{
		if (objectValues->getElementAt(i).getKey() == "id")
		{
			NumberValue* day = dynamic_cast<NumberValue*>(objectValues->getElementAt(i).getValue());
			this->id = (int)day->get();
		}
		else if (objectValues->getElementAt(i).getKey() == "name")
		{
			StringValue* name = dynamic_cast<StringValue*>(objectValues->getElementAt(i).getValue());
			this->name = name->get();
		}
		else
		{
			throw invalid_argument("Invalide argument content");
		}
	}
}

Subject::Subject(int id, std::string name)
{
	if (id < 1 || name.empty())
	{
		throw invalid_argument("Invalid arguments for Subject.");
	}

	this->id = id;
	this->name = name;
}

ObjectValue* Subject::deserialize() const
{
	ObjectValue* newSubject = new ObjectValue;
	newSubject->append(KeyValuePair{ "id", new NumberValue((double)id) });
	newSubject->append(KeyValuePair{ "name", new StringValue(name) });
	return newSubject;
}

int Subject::getId() const
{
	return id;
}

void Subject::setName(std::string name)
{
	if (name.empty())
	{
		throw invalid_argument("String is empty.");
	}
	this->name = name;
}