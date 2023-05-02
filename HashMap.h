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
		return hashMap[index];
	}
public:
	HashMap(int s):size(s),hashMap(new List<T> [s]){}
	~HashMap() { 
		delete[]hashMap; 
		hashMap = nullptr; 
	}

	int getSize() const { return size; };
	List<T>& operator[](int index)
	{
		return getAtIndex(index);
	}
};