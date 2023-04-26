#pragma once
#include "HashMap.h"
#include "Config.h"
#include "myString.h"

struct HashMapItem {
	const myString name;
	int index;
	HashMapItem(const myString* str):name(*str){}
};

template<typename T, typename hashType>
class Graph 
{
private:
	int vertexCount;
	T** vertices;
	HashMap<hashType> hashMap;
private:
	T*& getAtIndex(int index)
	{
		if (index >= 0 && index < vertexCount)
			return vertices[index];
		T* nullReturn = new T;
		return nullReturn;
	}
public:
	Graph(int size) :vertexCount(size), vertices(new T*[size]), hashMap(HashMap<hashType>(size*GRAPH_CAPACITY_MULTIPLIER)) {};
	~Graph()
	{
		for (int i = 0; i < vertexCount; i++)
		{
			delete vertices[i];
			vertices[i] = nullptr;
		}
		delete []vertices;
		vertices = nullptr;
	}

	HashMap<hashType>& getHashMap() { return hashMap; }
	int getSize() const { return vertexCount; }

	T*& operator[](int index)
	{
		return getAtIndex(index);
	};
};