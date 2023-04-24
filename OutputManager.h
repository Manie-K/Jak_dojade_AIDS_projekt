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
	int getIndexByName(const myString& str) const
	{
		for (int i = 0; i < graph->getSize(); i++)
		{
			if ((*graph)[i]->getName() == str)
				return i;
		}
	}
	int getIndexByPosition(const Coords_T& position) const
	{
		for (int i = 0; i < graph->getSize(); i++)
		{
			if ((*graph)[i]->getPos() == position)
				return i;
		}
	}
	
	int djikstra(const myString& srcName, const myString& destName,myString& path) const
	{
		const int size = graph->getSize();
		const int destIndex = getIndexByName(destName);
		int pathIndex = 0;
		int currentIndex = getIndexByName(srcName);
		int previousIndex = currentIndex;
		int *distances = new int[size];
		int *lastVisitsIndexes = new int[size];
		bool* visited = new bool[size];
		for (int i = 0; i < size; i++) {
			distances[i] = maxIntValue;
			lastVisitsIndexes[i] = -1;
			visited[i] = false;
		}
		distances[currentIndex] = 0;

		while (visited[destIndex]==false)
		{
			Node<Connection_T>* neighbour = (*graph)[currentIndex]->getFirstConnection();
			while (neighbour != nullptr)
			{
				if (neighbour->data.dest != nullptr) {
					int tempIndex = getIndexByName(neighbour->data.dest->getName());
					int tempDistance = neighbour->data.weight + distances[currentIndex];
					if(tempDistance < distances[tempIndex] && visited[tempIndex] == false) {
						distances[tempIndex] = tempDistance;
					}
				}
				neighbour = neighbour->next;
			}
			visited[currentIndex] = true;
			int newIndex = 0;
			int min = maxIntValue;
			for (int i = 0; i < size; i++)
			{
				int tmpInd = getIndexByName((*graph)[i]->getName()); //mozna bez tego?
				if (visited[tmpInd] == false && distances[tmpInd] < min)
				{
					newIndex = tmpInd;
					min = distances[newIndex];
				}
			}
			previousIndex = currentIndex;
			currentIndex = newIndex;
			//tutaj blad
			lastVisitsIndexes[currentIndex] = previousIndex;
		}
		int returnDistance = distances[destIndex];
		
		int x = destIndex;
		while (lastVisitsIndexes[x]!=-1)
		{
			x = lastVisitsIndexes[x];
			path += " ";
			path += (*graph)[x]->getName();
		}
		//
		delete[] distances;
		delete[] visited;
		delete[] lastVisitsIndexes;
		return returnDistance;
	}
public:
	OutputManager(const int tests, Graph<Vertex>* g):testCount(tests),graph(g),maxIntValue(INT_MAX){}
	~OutputManager() {}

	void run()
	{
		myString src, dest, type, path="";
		for (int i = 0; i < testCount; i++) {
			cin >> src >> dest >> type;
			path = "";
			int distance = djikstra(src, dest,path);
			if (type == "0")
				cout << distance << '\n';
			else if (type == "1")
			{
				cout << distance << path <<'\n';
			}
		}

	}
};

