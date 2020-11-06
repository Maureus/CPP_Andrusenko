#include "ExpandingContainer.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

template<typename T, int DefaultCapacity, int ExpansionRatio>
bool ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::HasEmptySpace() const
{
	return numberOfElements < fieldSize;
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
void ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::Expand()
{	
	fieldSize = fieldSize * ExpansionRatio;
	T* tempField = new T[fieldSize];

	for (int i = 0; i < numberOfElements; i++)
	{
		tempField[i] = field[i];
	}	
	
	delete[] field;
	field = tempField;

	/*fieldSize = fieldSize * ExpansionRatio;
	T* tempField = new T[numberOfElements];

	for (int i = 0; i < numberOfElements; i++)
	{
		tempField[i] = field[i];
	}

	delete[] field;
	field = new T[fieldSize];

	for (int i = 0; i < numberOfElements; i++)
	{
		field[i] = tempField[i];
	}	

	delete[] tempField;*/
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::ExpandingContainer()
{
	field = new T[DefaultCapacity];	
	fieldSize = DefaultCapacity;
	numberOfElements = 0;
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::~ExpandingContainer()
{	
	delete[] field;
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
void ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::Add(const T& obj)
{
	if (!HasEmptySpace())
	{
		Expand();
	}	
	field[numberOfElements++] = obj;	
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
T& ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::operator[](int index)
{
	if (index < 0 || index >= numberOfElements)
	{
		throw out_of_range("Index is out of range!");
	}

	return field[index];
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
T ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::operator[](int index) const {
	if (index < 0 || index >= numberOfElements)
	{
		throw out_of_range("Index is out of range!");
	}

	return field[index];
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
unsigned int ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::Size() const
{
	return numberOfElements;
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
void ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::AddAtIndex(int index, const T& obj)
{
	if (index < 0 || index > numberOfElements)
	{
		std::ostringstream os;
		os << "Array indexing violation! Index can't be negative and the last index you can add at is: " << numberOfElements << "!";
		throw out_of_range(os.str());
	}

	if (!HasEmptySpace())
	{
		Expand();

		for (int i = numberOfElements; i > index; i--)
		{
			field[i] = field[i - 1];
		}
		field[index] = obj;
		numberOfElements++;
	}
	else
	{
		for (int i = numberOfElements; i > index; i--)
		{
			field[i] = field[i - 1];
		}
		field[index] = obj;
		numberOfElements++;
	}
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
void ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::DeleteAtIndex(int index)
{
	if (index < 0 || index >= numberOfElements)
	{
		throw out_of_range("Index is out of range!");
	}
	
	for (int i = index; i < numberOfElements; i++)
	{
		field[i] = field[i+1];		
	}

	numberOfElements--;	
}

template
class ExpandingContainer<int, 5, 2>;

template
class ExpandingContainer<string, 5, 2>;
