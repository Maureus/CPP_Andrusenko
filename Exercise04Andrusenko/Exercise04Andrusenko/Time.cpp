#include "Time.h"

#include <sstream>
#include <iostream>
#include <string>
#include <exception>

Time::Time()
{	
}

Time::~Time()
{
}

Time::Time(int hour, int minute, int second)
{
	if (hour <= 24 && minute <= 60 && second <= 60 && hour >= 0 && minute >= 0 && second >= 0)
	{
		this->hour = hour;
		this->minute = minute;
		this->second = second;
	}
	else
	{
		throw std::invalid_argument("Not allowed number");
	}
	
}

int Time::CompareTo(IComparable* object) const
{
	if (object == nullptr)
	{
		throw std::invalid_argument("Invalid Argument");
	}

	Time* ptr = dynamic_cast<Time*>(object);

	if (ptr == nullptr)
	{
		throw std::invalid_argument("Invalid Argument");
	}

	int timeToSec = second + minute * 60 + hour * 60 * 60;
	int timeToSecFromPtr = ptr->second + ptr->minute * 60 + ptr->hour * 60 * 60;

	if (timeToSec == timeToSecFromPtr)
	{		
		return 0;
	}
	else if (timeToSec > timeToSecFromPtr)
	{		
		return 1;
	}
	else
	{		
		return -1;
	}
}

std::string Time::ToString() const
{
	std::ostringstream os;

	hour < 10 ? os << "0" << hour << ":" : os << hour << ":";
	minute < 10 ? os << "0" << minute << ":" : os << minute << ":";
	second < 10 ? os << "0" << second : os << second;	
	 
	return os.str();
}
