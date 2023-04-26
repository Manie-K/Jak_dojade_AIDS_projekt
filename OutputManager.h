#pragma once
#include <iostream>
#include "Vertex.h"
#include "MinHeap.h"

using namespace std;

class OutputManager
{
private:
	const int testCount;
	const int maxIntValue;
	Graph<Vertex, HashMapItem>* graph;
private:
	int getIndexByName(const myString& str) const;
	
	int findPath(const myString& srcName, const myString& destName, myString& path, bool commandTypeOne) const;
	int hash(const myString& key) const;
public:
	OutputManager(const int tests, Graph<Vertex, HashMapItem>* g);
	~OutputManager();

	void run();
};

