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
	Graph<Vertex>* graph;
private:
	int getIndexByName(const myString& str) const;
	
	int findPath(const myString& srcName, const myString& destName, bool commandTypeOne) const;
	int hash(const char* key) const;
public:
	OutputManager(const int tests, Graph<Vertex>* g);
	~OutputManager();

	void run();
};

