#include "OutputManager.h"

int OutputManager::getIndexByName(const myString& str) const
{
	for (int i = 0; i < graph->getSize(); i++)
	{
		if ((*graph)[i]->getName() == str)
			return i;
	}
	return -1;
}
int OutputManager::getIndexByPosition(const Coords_T& position) const
{
	for (int i = 0; i < graph->getSize(); i++)
	{
		if ((*graph)[i]->getPos() == position)
			return i;
	}
	return -1;
}

int OutputManager::djikstra(const myString& srcName, const myString& destName, myString& path, bool commandTypeOne) const
{
	const int size = graph->getSize();
	const int destIndex = getIndexByName(destName);
	int currentIndex = getIndexByName(srcName);
	int srcIndex = currentIndex;
	int previousIndex = currentIndex;
	int* distances = new int[size];
	int* lastVisitsIndexes = new int[size];
	bool* visited = new bool[size];
	for (int i = 0; i < size; i++) {
		distances[i] = maxIntValue;
		lastVisitsIndexes[i] = -1;
		visited[i] = false;
	}
	distances[currentIndex] = 0;

	while (visited[destIndex] == false)
	{
		Node<Connection_T>* neighbour = (*graph)[currentIndex]->getFirstConnection();
		while (neighbour != nullptr)
		{
			if (neighbour->data.dest != nullptr) {
				int tempIndex = getIndexByName(neighbour->data.dest->getName());
				int tempDistance = neighbour->data.weight + distances[currentIndex];
				if (tempDistance < distances[tempIndex] && visited[tempIndex] == false) {
					distances[tempIndex] = tempDistance;
					lastVisitsIndexes[tempIndex] = currentIndex;
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
	}
	int returnDistance = distances[destIndex];

	int x = destIndex;
	int pathIndex = 0;
	myString* pathArray = new myString[size];
	if (commandTypeOne) {
		while (lastVisitsIndexes[x] != -1 && lastVisitsIndexes[x] != srcIndex)
		{
			x = lastVisitsIndexes[x];
			pathArray[pathIndex++] = (*graph)[x]->getName();
		}
	}
	while (pathIndex >= 0)
	{
		path += " ";
		path += pathArray[pathIndex--];
	}

	delete[] distances;
	delete[] visited;
	delete[] lastVisitsIndexes;
	delete[] pathArray;
	return returnDistance;
}

OutputManager::OutputManager(const int tests, Graph<Vertex>* g) :testCount(tests), graph(g), maxIntValue(INT_MAX) {}
OutputManager::~OutputManager() {}

void OutputManager::run()
{
	myString src, dest, type, path = "";
	int distance;
	for (int i = 0; i < testCount; i++) {
		cin >> src >> dest >> type;
		path = "";
		if (type == "0") {
			distance = djikstra(src, dest, path, false);
			cout << distance << '\n';
		}
		else if (type == "1")
		{
			distance = djikstra(src, dest, path, true);
			cout << distance << path << '\n';
		}
	}

}


