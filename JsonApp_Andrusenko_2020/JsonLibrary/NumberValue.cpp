#include "pch.h"
#include "api.h"

NumberValue::NumberValue(double value)
{
	this->value = value;
}

double NumberValue::get() const
{
	return value;
}

std::string NumberValue::serialize() const
{
	ostringstream oss;
	oss << value;
	return oss.str();
}