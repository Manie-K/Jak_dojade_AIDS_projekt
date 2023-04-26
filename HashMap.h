#pragma once
#include "List.h"

template<typename T>
class HashMap
{
private:
	int size;
	List<T>* hashMap;
private:
	List<T>& getAtIndex(int index)
	{
		if (index >= 0 && index < size)
		{
			return hashMap[index];
		}
		List<T> temp;
		return temp;
	}
public:
	HashMap(int s):size(s),hashMap(new List<T> [s]){}
	~HashMap() { delete[]hashMap; }

	int getSize()const { return size; };
	List<T>& operator[](int index)
	{
		return getAtIndex(index);
	}
};