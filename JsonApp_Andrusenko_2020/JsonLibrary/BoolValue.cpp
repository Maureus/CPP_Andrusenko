#include "pch.h"
#include "api.h"

BoolValue::BoolValue(bool value)
{
	this->value = value;
}

bool BoolValue::get() const
{
	return value;
}

std::string BoolValue::serialize() const
{
	return value ? "true" : "false";
}

BoolValue BoolValue::deserialize(const std::string& value)
{
	if (value == "true")
	{
		return BoolValue(true);
	}
	else if (value == "false")
	{
		return BoolValue(false);
	}

	return "???";
}