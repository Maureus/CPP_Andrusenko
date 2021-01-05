#include "pch.h"
#include "api.h"

KeyValuePair::KeyValuePair() = default;

KeyValuePair::KeyValuePair(std::string key, Value * value)
{
	if (key.empty() || value == nullptr)
	{
		throw invalid_argument("String is empry or value is nullptr");
	}

	this->key = key;
	this->value = value;
}

KeyValuePair::~KeyValuePair()
{
}

std::string KeyValuePair::getKey() const
{
	return key;
}

Value* KeyValuePair::getValue() const
{
	return value;
}