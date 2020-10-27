#pragma once

#include "IObject.h"
#include "IComparable.h"

class Time : public IComparable
{
private:
	int second;
	int minute;
	int hour;
public:
	Time();
	~Time();
	Time(int hour, int minute, int second);
	int CompareTo(IComparable* object) const override;
	std::string ToString() const override;
};

