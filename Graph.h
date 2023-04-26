#pragma once
#include "List.h"

template<typename T>
class Graph 
{
private:
	int vertexCount;
	List<T*>* vertices;

private:
	List<T*>& getAtIndex(int index)
	{
		if (index >= 0 && index < vertexCount)
			return vertices[index];
		T* nullReturn = new T;
		return nullReturn;
	}
public:
	Graph(int size) :vertexCount(size), vertices(new List<T*> [size]) {};
	~Graph()
	{
		for (int i = 0; i < vertexCount; i++)
		{
			delete vertices[i];
			vertices[i] = nullptr;
		}
		delete vertices;
		vertices = nullptr;
	}

	int getSize() const { return vertexCount; }

	List<T*>& operator[](int index)
	{
		return getAtIndex(index);
	};
};