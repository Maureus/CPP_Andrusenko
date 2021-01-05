#include "pch.h"
#include "api.h"

StringValue::StringValue(std::string value)
{
	this->value = value;
}

std::string StringValue::get() const
{
	return value;
}

std::string StringValue::serialize() const
{
	ostringstream oss;
	oss << '\"';
	oss << value;
	oss << '\"';
	return oss.str();
}