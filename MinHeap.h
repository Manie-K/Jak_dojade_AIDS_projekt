#pragma once

struct HeapItem {
	int distance;
	int index;
	bool visited;
	bool operator>(const HeapItem& other)
	{
		return distance > other.distance;
	}

	bool operator<(const HeapItem& other)
	{
		return distance < other.distance;
	}
};
class MinHeap
{
private:
	HeapItem* array;
	int size;
	int cap;
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
	void swap(HeapItem* a, HeapItem* b)
	{
		HeapItem temp = *b;
		*b = *a;
		*a = temp;
	}
	int parentIndex(int index) { return (index - 1) / 2; }
	int rightChildIndex(int index) { return 2 * index + 2; }
	int leftChildIndex(int index) { return 2 * index + 1; }
public:
	MinHeap(int capacity):array(new HeapItem[capacity]), size(0), cap(capacity){}
	~MinHeap() { delete[] array; }

	bool isEmpty() const { return size <= 0; }
	void push(HeapItem item)
	{
		if (size >= cap)
		{
			HeapItem* tempArray = new HeapItem[size];
			for (int i = 0; i < size; i++)
			{
				tempArray[i] = array[i];
			}
			delete[] array;
			cap *= 2;
			array = new HeapItem[cap];
			for (int i = 0; i < size; i++)
			{
				array[i] = tempArray[i];
			}
			delete[] tempArray;
		}
		size++;
		int index = size - 1;
		array[index] = item;
		minimalHeapifyUp(index);
	}
	HeapItem getMin()
	{
		if(size>0)
			return array[0];
		return HeapItem();
	}
	HeapItem popMin()
	{
		if (size <= 0)
			return HeapItem();
		if (size == 1)
		{
			size--;
			return array[0];
		}
		HeapItem tempReturn = array[0];
		array[0] = array[size - 1];
		size--;
		minimalHeapifyDown(0);
		return tempReturn;
	}
};