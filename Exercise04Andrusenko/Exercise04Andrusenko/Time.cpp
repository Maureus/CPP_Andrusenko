#include "Time.h"

#include <sstream>
#include <iostream>
#include <string>
#include <exception>

Time::Time()
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

int Time::CompareTo(IComparable* object)
{
	Time* ptr = dynamic_cast<Time*>(object);

	if (ptr == nullptr)
	{
		throw std::invalid_argument("Invalid Argument");
	}

	int timeToInt = 0;
	int timeToIntFromPtr = 0;

	timeToInt = second + minute * 100 + hour * 10000;
	timeToIntFromPtr = ptr->second + ptr->minute * 100 + ptr->hour * 10000;

	if (timeToInt == timeToIntFromPtr)
	{		
		return 0;
	}
	else if (timeToInt > timeToIntFromPtr)
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
	os << hour << ":";
	if (minute < 10)
	{
		os << "0" << minute << ":";
	}
	else 
	{
		os << minute << ":";
	}

	if (second < 10)
	{
		os << "0" << second;
	}
	else
	{
		os << second;
	}
	 
	std::string timeToStr = os.str();
	return timeToStr;
}
