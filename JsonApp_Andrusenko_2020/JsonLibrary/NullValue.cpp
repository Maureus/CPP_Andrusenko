#include "pch.h"
#include "api.h"

bool NullValue::operator==(const NullValue& other) const
{
	return true;
}

std::string NullValue::serialize() const
{
	return "null";
}