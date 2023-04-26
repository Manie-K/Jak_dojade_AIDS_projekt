#pragma once
#include <iostream>
#include "Graph.h"
#include "Vertex.h"
#include "String.h"

using namespace std;

class OutputManager
{
private:
	const int testCount;
	const int maxIntValue;
	Graph<Vertex>* graph;
private:
	int getIndexByName(const myString& str) const;
	int getIndexByPosition(const Coords_T& position) const;
	
	int djikstra(const myString& srcName, const myString& destName, myString& path, bool commandTypeOne) const;
	int hash(const myString& key) const;
public:
	OutputManager(const int tests, Graph<Vertex>* g);
	~OutputManager();

	void run();
};

