#include "pch.h"
#include "JsonException.h"

JsonException::JsonException(const std::string& msg) :
	message(msg)
{
}

const char* JsonException::what() const throw()
{
	return message.c_str();
}