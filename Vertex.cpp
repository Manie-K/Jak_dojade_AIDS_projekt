#include "Vertex.h"

Vertex::Vertex() :name(""), pos({ 0,0 }) {}
Vertex::~Vertex() {};

myString Vertex::getName() const { return name; }
void Vertex::setName(const myString& str) { name = str; }

Coords_T Vertex::getPos() const { return pos; }
void Vertex::setPos(const Coords_T& position) { pos = position; }

void Vertex::addConnection(Vertex*& dest, int distance)
{
	Node<Connection_T>* temp = new Node<Connection_T>;
	temp->data.dest = dest;
	temp->data.weight = distance;
	connectionList.addFirst(*temp);
}
Node<Connection_T>* Vertex::getFirstConnection()
{
	return connectionList.getFirst();
}