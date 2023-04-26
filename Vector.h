#pragma once
#include "myString.h"

template<typename T>
class Vector
{
private:
	const int doubleExtensionStop = 200;
	int size;
	int capacity;
	T* array;
private:
	void extend()
	{
		T* tempArray = new T[size];
		for (int i = 0; i < size; i++)
			tempArray[i] = array[i];
		delete[]array;
		array = new T[capacity];
		for (int i = 0; i < size; i++)
			array[i] = tempArray[i];
		delete[] tempArray;
	}
public:
	Vector() :size(0), capacity(0), array(nullptr){}
	~Vector() { delete[] array; }
	
	int getSize() const { return size; }
	int getCapacity() const { return capacity; }

	void pushBack(T& item)
	{
		if (array == nullptr)
		{
			array = new T[1];
			capacity = 1;
			size = 0;
		}
		if (size < capacity)
		{
			array[size++] = item;
			return;
		}
		capacity = capacity < doubleExtensionStop ? capacity * 2 : capacity + capacity / 3;
		extend();
		array[size++] = item;
	}

	T& operator[](int index)
	{
		if(index >= 0 && index < size)
			return array[index];
		return T();
	}
};