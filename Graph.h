#pragma once

template<typename T>
class Graph 
{
private:
	int vertexCount;
	T** vertices;

private:
	T*& getAtIndex(int index) 
	{
		if (index >= 0 && index < vertexCount)
			return vertices[index];
	}
public:
	Graph(int size) :vertexCount(size), vertices(new T* [size]) {};
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

	T*& operator[](int index)
	{
		return getAtIndex(index);
	};
};