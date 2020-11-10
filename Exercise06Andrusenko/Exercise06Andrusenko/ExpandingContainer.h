#pragma once

#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

template<typename T, int DefaultCapacity = 5, int ExpansionRatio = 2>
class ExpandingContainer
{	
	T* array;
	unsigned int arraySize;
	unsigned int numberOfElements;
	bool HasEmptySpace() const;
	void Expand();

public:
	ExpandingContainer();
	~ExpandingContainer();
	void Add(const T& obj);
	T& operator[](int index);
	T operator[](int index) const;
	unsigned int Size() const;
	void AddAtIndex(int index, const T& obj);
	void DeleteAtIndex(int index);	
};

template<typename T, int DefaultCapacity, int ExpansionRatio>
bool ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::HasEmptySpace() const
{
	return numberOfElements < arraySize;
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
void ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::Expand()
{
	arraySize = arraySize * ExpansionRatio;
	T* tempField = new T[arraySize];

	for (int i = 0; i < numberOfElements; i++)
	{
		tempField[i] = array[i];
	}

	delete[] array;
	array = tempField;

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
	array = new T[DefaultCapacity];
	arraySize = DefaultCapacity;
	numberOfElements = 0;
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::~ExpandingContainer()
{
	delete[] array;
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
void ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::Add(const T& obj)
{
	if (!HasEmptySpace())
	{
		Expand();
	}
	array[numberOfElements++] = obj;
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
T& ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::operator[](int index)
{
	if (index < 0 || index >= numberOfElements)
	{
		throw out_of_range("Index is out of range!");
	}

	return array[index];
}

template<typename T, int DefaultCapacity, int ExpansionRatio>
T ExpandingContainer<T, DefaultCapacity, ExpansionRatio>::operator[](int index) const {
	if (index < 0 || index >= numberOfElements)
	{
		throw out_of_range("Index is out of range!");
	}

	return array[index];
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
			array[i] = array[i - 1];
		}
		array[index] = obj;
		numberOfElements++;
	}
	else
	{
		for (int i = numberOfElements; i > index; i--)
		{
			array[i] = array[i - 1];
		}
		array[index] = obj;
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
		array[i] = array[i + 1];
	}

	numberOfElements--;
}


