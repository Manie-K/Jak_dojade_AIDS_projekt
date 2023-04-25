#pragma once
#include "Node.h"

template <typename T>
class List
{
private:
	Node<T>* first;
	Node<T>* last;
	size_t size;
public:
	List() :size(0), first(nullptr), last(nullptr) {}
	List(const List<T>& other) : size(other.size), first(other.first), last(other.last) {};
	~List() {
		Node<T>* current = first;
		while (current!=nullptr) {
			Node<T>* next = current->next;
			delete current;
			current = next;
		}
		size = 0;
	}

	size_t getSize() const { 
		if (first == nullptr)
			return 0;
		return size; 
	}
	void addFirst(Node<T>& node)
	{
		if (size == 0)
		{
			first = &node;
			first->next = nullptr;
			first->prev = nullptr;
			last = first;
			size = 1;
			return;
		}
		node.next = first;
		node.prev = nullptr;
		if(first!=nullptr)
			first->prev = &node;
		first = &node;
		size++;
	}
	void addLast(Node<T>& node)
	{
		if (size == 0)
		{
			addFirst(node);
			return;
		}
		node.next = nullptr;
		node.prev = last;
		if(last!=nullptr)
			last->next = &node;
		last = &node;
		size++;
	}
	Node<T>* getFirst(){return first; }
	Node<T>* getLast(){ return last; }
	Node<T>* getAt(int index)
	{
		if (index == 0)
			return getFirst();
		if (index == size - 1)
			return getLast();
		if (index < 0 || index > size - 1)
			return nullptr;
		Node<T>* temp = first;
		int i = 0;
		while (temp != nullptr && i < index)
		{
			i++;
			temp = temp->next;
		}
		return temp;
	}
	
	void deleteFirst()
	{
		if (size <= 0)
			return;
		if (size == 1)
		{
			delete first;
			first = nullptr;
			last = nullptr;
			size--;
		}
		if (first != nullptr&&first->next!=nullptr) {
			first = first->next;
			delete first->prev;
			first->prev = nullptr;
			size--;
			return;
		}
	}
	void deleteLast()
	{
		if (size <= 0)
			return;
		if (size == 1)
		{
			deleteFirst();
			return;
		}
		if (last != nullptr && last->prev!=nullptr)
		{
			last = last->prev;
			delete last->next;
			last->next = nullptr;
			size--;
			return;
		}
	}
	void deleteAt(int index)
	{
		if (size == 0 || index < 0 || index > size - 1)
			return;
		if (index == 0)
		{
			deleteFirst();
			return;
		}
		if (index == size - 1)
		{
			deleteLast();
			return;
		}
		size--;
		Node<T>* temp = first;
		int i = 0;
		while (i < index && temp != nullptr)
		{
			i++;
			temp = temp->next;
		}
		if (temp == nullptr){
			return;
		}

		if (temp->next != nullptr)
		{
			temp->next->prev = temp->prev;
		}
		if(temp->prev != nullptr)
		{
			temp->prev->next = temp->next;
		}
		delete temp;
		temp = nullptr;
	}
};