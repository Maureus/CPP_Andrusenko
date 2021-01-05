#include "pch.h"
#include "api.h"

ArrayValue::ArrayValue()
{
	arrayValue = new DynamicArray<Value*>;
};

ArrayValue::~ArrayValue()
{
	for (int i = 0; i < arrayValue->getSize(); i++)
	{
		delete arrayValue->getElementAt(i);
	}
	delete arrayValue;
};

void ArrayValue::append(Value* element)
{
	if (element == nullptr)
	{
		throw invalid_argument("Element is nullptr");
	}

	arrayValue->append(element);
}

std::string ArrayValue::serialize() const
{
	ostringstream oss;
	oss << '[';
	int size = arrayValue->getSize();
	for (int i = 0; i < size; i++)
	{
		oss << arrayValue->getElementAt(i)->serialize();
		if (i != size - 1)
		{
			oss << ',';
		}
	}
	oss << ']';
	return oss.str();
}

DynamicArray<Value*>* ArrayValue::getValues() const
{
	return arrayValue;
}