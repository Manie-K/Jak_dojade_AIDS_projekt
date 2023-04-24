#pragma once
#include "List.h"

template <typename T>
class Queue
{
private:
	List<T> list;
	size_t size;
public:
	Queue()
	{
		size = 0;
	}
	~Queue(){}

	size_t getSize() const { return size; }
	
	void push(T data)
	{
		Node<T> *temp = new Node<T>(data);
		list.addFirst(*temp);
		size++;
	}
	T pop()
	{
		if (size == 0)
			return NULL;
		Node<T> temp = *(list.getLast());
		size--;
		list.deleteLast();
		return temp.data;
	}
	
	void display() const
	{
		Node<T>* temp = list.getFirst();
		for (int i = 0; i < size; i++)
		{
			if (temp == nullptr)
				return;
			cout <<i << " " << temp->data << '\n';
			temp = temp->next;
		}
	}
};