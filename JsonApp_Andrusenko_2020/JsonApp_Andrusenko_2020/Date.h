#ifndef DATE_H
#define DATE_H

#include <api.h>

class Date
{
	int day;
	int month;
	int year;
public:
	Date() = default;
	Date(ObjectValue* object);
	Date(int day, int month, int year);
	~Date() = default;
	ObjectValue* createObject() const;
};

#endif // !DATE_H