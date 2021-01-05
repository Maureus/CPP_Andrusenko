#include "pch.h"
#include "api.h"

ObjectValue::ObjectValue()
{
	objectValue = new DynamicArray<KeyValuePair>;
}

ObjectValue::~ObjectValue()
{
	for (int i = 0; i < objectValue->getSize(); i++)
	{
		delete objectValue->getElementAt(i).getValue();
	}
	delete objectValue;
};

void ObjectValue::append(const KeyValuePair& pair)
{
	objectValue->append(pair);
}

std::string ObjectValue::serialize() const
{
	ostringstream oss;
	oss << '{';
	int size = objectValue->getSize();
	for (int i = 0; i < size; i++)
	{
		KeyValuePair pair = objectValue->getElementAt(i);
		oss << '\"';
		oss << pair.getKey();
		oss << '\"';
		oss << ':';
		oss << pair.getValue()->serialize();
		if (i != size - 1)
		{
			oss << ',';
		}
	}
	oss << '}';
	return oss.str();
}

DynamicArray<KeyValuePair>* ObjectValue::getValues() const
{
	return objectValue;
}