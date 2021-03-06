#include "Date.h"
#include <stdexcept>

using namespace std;

ostream& operator<<(ostream& os, const Date& date)
{
	os << date.day << '.' << date.month << '.' << date.year;
	return os;
}

std::istream& operator>>(std::istream& is, Date& date)
{	
	char empty;
	is >> date.day >> empty >> date.month >> empty >> date.year;
	return is;
}

Date::Date()
{
}

Date::Date(int day, int month, int year)
{
	if (day <= 0 or day > 31 or month <= 0 or month > 12 or year <= 0)
	{
		throw invalid_argument("Unacceptable date!");
	}

	this->day = day;
	this->month = month;
	this->year = year;	
}

Date::~Date()
{
}
