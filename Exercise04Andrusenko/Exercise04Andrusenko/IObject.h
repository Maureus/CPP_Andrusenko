#pragma once
#include <iostream>
#include <string>

class IObject
{
public:
	virtual ~IObject() {};
	virtual std::string ToString() const = 0;
};
