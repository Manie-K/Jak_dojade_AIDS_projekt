#pragma once
#include "myString.h"
#include "Queue.h"


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
	Vertex():name(""),pos({0,0}){}
	~Vertex() {};
	
	myString getName() const { return name; }
	void setName(const myString& str) { name = str; }

	Coords_T getPos() const { return pos; }
	void setPos(const Coords_T& position) { pos = position; }

	void addConnection(Vertex*& dest, int distance)
	{
		Node<Connection_T>* temp = new Node<Connection_T>;
		temp->data.dest = dest;
		temp->data.weight = distance;
		connectionList.addFirst(*temp);
	}

};