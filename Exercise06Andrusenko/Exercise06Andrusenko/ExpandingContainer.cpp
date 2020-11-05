#include "ExpandingContainer.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T, int start>
bool ExpandingContainer<T, start>::HasEmptySpace() const
{
	return numberOfElements < fieldSize;
}

template<typename T, int start>
void ExpandingContainer<T, start>::Expand()
{	
	T* tempField = new T[numberOfElements]();

	for (int i = 0; i < numberOfElements; i++)
	{
		tempField[i] = field[i];
	}

	fieldSize = fieldSize * expansionRatio;
	field = new T[fieldSize];

	for (int i = 0; i < numberOfElements; i++)
	{
		field[i] = tempField[i];
	}	

	delete[] tempField;	
}

template<typename T, int start>
ExpandingContainer<T, start>::ExpandingContainer()
{
	field = new T[startSize]();
	fieldSize = startSize;
	numberOfElements = 0;
}

template<typename T, int start>
ExpandingContainer<T, start>::~ExpandingContainer()
{
	//delete[] field; // ??????
}

template<typename T, int start>
void ExpandingContainer<T, start>::Add(const T& obj)
{
	if (!HasEmptySpace())
	{
		Expand();
	}	
	field[numberOfElements++] = obj;	
}

template<typename T, int start>
T& ExpandingContainer<T, start>::operator[](int index)
{
	if (index < 0 || index >= numberOfElements)
	{
		throw std::out_of_range("Index is out of range!");
	}

	return field[index];
}

template<typename T, int start>
T ExpandingContainer<T, start>::operator[](int index) const {
	if (index < 0 || index >= numberOfElements)
	{
		throw std::out_of_range("Index is out of range!");
	}

	return field[index];
}

template<typename T, int start>
unsigned int ExpandingContainer<T, start>::Size() const
{
	return numberOfElements;
}

template<typename T, int start>
void ExpandingContainer<T, start>::AddOnIndex(int index, const T& obj)
{
}

template<typename T, int start>
void ExpandingContainer<T, start>::DeleteOnIndex(int index)
{
}

template
class ExpandingContainer<int, 5>;
