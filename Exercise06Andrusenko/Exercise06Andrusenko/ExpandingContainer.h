#pragma once

template<typename T, int DefaultCapacity = 5, int ExpansionRatio = 2>
class ExpandingContainer
{	
	T* field;
	unsigned int fieldSize;
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

