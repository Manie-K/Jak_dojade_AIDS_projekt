#pragma once
#include "myString.h"
#include "Queue.h"
#include "Graph.h"


struct Coords_T {
	int x, y;
	bool operator==(const Coords_T& other)
	{
		return (x == other.x && y == other.y);
	}
};

class Vertex;

struct Connection_T {
	int weight;
	Vertex* dest;
};

class Vertex
{
private:
	myString name;
	Coords_T pos;
	List<Connection_T> connectionList;
public:
	Vertex();
	~Vertex();

	myString getName() const;
	void setName(const myString& str);

	Coords_T getPos() const;
	void setPos(const Coords_T& position);

	void addConnection(Vertex*& dest, int distance);
	Node<Connection_T>* getFirstConnection();
};