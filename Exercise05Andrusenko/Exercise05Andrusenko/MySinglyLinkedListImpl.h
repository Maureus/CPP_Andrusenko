#pragma once

#include <stdexcept>

template<typename T>
class MySingleLinkedListImpl
{
private:

	template<typename E>
	struct Node
	{
		E data = nullptr;
		Node<E>* next = nullptr;

		Node(E data, Node<E> *next) : data(data), next(next) {}
	};

	int size = 0;
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;

public:
	MySingleLinkedListImpl();
	~MySingleLinkedListImpl();
	int GetSize() const;
	void Add(T data);
	T GetOnIndex(int index) const;
};

template<typename T>
MySingleLinkedListImpl<T>::MySingleLinkedListImpl()
{	
}

template<typename T>
MySingleLinkedListImpl<T>::~MySingleLinkedListImpl()
{	
	while (head != nullptr) {
		Node<T>* temp = head;
		head = head->next;
		delete temp;
	}
}

template<typename T>
inline int MySingleLinkedListImpl<T>::GetSize() const
{
	return size;
}

template<typename T>
inline void MySingleLinkedListImpl<T>::Add(T data)
{
	auto* newNode = new Node<T>(data, nullptr);
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		tail = newNode;
	}
	size++;
}

template<typename T>
inline T MySingleLinkedListImpl<T>::GetOnIndex(int index) const
{
	if (index < 0 || index >= size)
	{
		throw std::out_of_range("Index is out of range!");
	}
	
	Node<T>* node = head;
	for (int i = 0; i < index; ++i)
	{
		node = node->next;
	}

	return node->data;	
}
