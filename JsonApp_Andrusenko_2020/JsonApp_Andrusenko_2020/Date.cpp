#include "Date.h"

Date::Date(ObjectValue* object)
{
	DynamicArray<KeyValuePair>* objectValues = object->getValues();
	for (int i = 0; i < objectValues->getSize(); i++)
	{
		if (objectValues->getElementAt(i).getKey() == "day")
		{
			NumberValue* day = dynamic_cast<NumberValue*>(objectValues->getElementAt(i).getValue());
			this->day = (int)day->get();
		}
		else if (objectValues->getElementAt(i).getKey() == "month")
		{
			NumberValue* month = dynamic_cast<NumberValue*>(objectValues->getElementAt(i).getValue());
			this->month = (int)month->get();
		}
		else if (objectValues->getElementAt(i).getKey() == "year")
		{
			NumberValue* year = dynamic_cast<NumberValue*>(objectValues->getElementAt(i).getValue());
			this->year = (int)year->get();
		}
	}
}

Date::Date(int day, int month, int year)
{
	if (day < 1 || day > 31 || month < 0 || month > 12 || year < 1950 || year > 2020)
	{
		throw std::invalid_argument("Invalide date format.");
	}
	this->day = day;
	this->month = month;
	this->year = year;
}

ObjectValue* Date::createObject() const
{
	ObjectValue* newDate = new ObjectValue;
	newDate->append(KeyValuePair("day", new NumberValue(day)));
	newDate->append(KeyValuePair("month", new NumberValue(month)));
	newDate->append(KeyValuePair("year", new NumberValue(year)));
	return newDate;
}