#pragma once

#include "IObject.h"

class IComparable
{
public:
	virtual ~IComparable() {};
	virtual int CompareTo(IComparable* object) const = 0;
};
