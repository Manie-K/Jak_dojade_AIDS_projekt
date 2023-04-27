#pragma once
#include "HashMap.h"
#include "Config.h"
#include "myString.h"

struct HashMapItem {
	const myString name;
	int index;
	HashMapItem(const myString* str):name(*str),index(0){}
};

template<typename T>
class Graph 
{
private:
	int vertexCount;
	T** vertices;
	HashMap<HashMapItem> hashMap;
private:
	T*& getAtIndex(int index)
	{
		return vertices[index];
	}
public:
	Graph(int size) :vertexCount(size), vertices(new T*[size]), hashMap(HashMap<HashMapItem>(GRAPH_CAPACITY_MULTIPLIER)) {};
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

	HashMap<HashMapItem>& getHashMap() { return hashMap; }
	int getSize() const { return vertexCount; }

	T*& operator[](int index)
	{
		return getAtIndex(index);
	};
};