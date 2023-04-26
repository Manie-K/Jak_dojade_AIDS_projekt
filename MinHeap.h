#pragma once
//#include "Vector.h"
//implementation with array not vector, updating not adding new items
template<typename T>
class MinHeap
{
private:
	T* array;
	int size;
	const int cap;
private:
	void minimalHeapifyDown(int index)
	{
		int right = rightChildIndex(index);
		int left = leftChildIndex(index);
		int minimal = index;
		if (array[index] > array[right] && right > 0 && right < size)
			minimal = right;
		if (array[index] > array[left] && left > 0 && left < size)
			minimal = left;
		if (minimal != index)
		{
			swap(&array[index], &array[minimal]);
			minimalHeapifyDown(minimal);
		}
	}
	void minimalHeapifyUp(int index)
	{
		while (index > 0 && array[parentIndex(index)] > array[index])
		{
			swap(&array[parentIndex(index)], &array[index]);
			index = parentIndex(index);
		}
	}
	void swap(T* a, T* b)
	{
		T temp = *b;
		*b = *a;
		*a = temp;
	}
	int parentIndex(int index) { return (index - 1) / 2; }
	int rightChildIndex(int index) { return 2 * index + 2; }
	int leftChildIndex(int index) { return 2 * index + 1; }
	void decreaseValue(int index, T value)
	{
		array[index] = value;
		minimalHeapifyUp(index);
	}
	int findByValue(T value)
	{
		for (int i = 0; i < size; i++)
		{
			if (array[i] == value)
				return i;
		}
		return -1;
	}
public:
	MinHeap(int capacity):array(new T[capacity]), size(0), cap(capacity){}
	~MinHeap() { delete[]array; }

	bool isEmpty() const { return size <= 0; }
	void update(T valToFind, T newVal)
	{
		int index = findByValue(valToFind);
		decreaseValue(index, newVal);
	}
	void push(T item)
	{
		if (size >= cap)
			return;
		size++;
		int index = size - 1;
		array[index] = item;
		minimalHeapifyUp(index);
	}
	T getMin()
	{
		if(size>0)
			return array[0];
		return T();
	}
	T popMin()
	{
		if (size <= 0)
			return T();
		if (size == 1)
		{
			size--;
			return array[0];
		}
		T tempReturn = array[0];
		array[0] = array[size - 1];
		size--;
		minimalHeapifyDown(0);
		return tempReturn;
	}
};