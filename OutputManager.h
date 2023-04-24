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
	const Graph<Vertex>* graph;
private:
public:
	OutputManager(const int tests,  const Graph<Vertex>* g):testCount(tests),graph(g){}
	~OutputManager() {}

	void run()
	{
		myString src, dest, type;
		cin >> src >> dest >> type;
	}
};

