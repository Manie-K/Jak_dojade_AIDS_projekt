#include "OutputManager.h"

int OutputManager::getIndexByName(const myString& str) const
{
	int index = 0;
	int hashIndex = hash(str);
	Node<HashMapItem>* temp = graph->getHashMap()[hashIndex].getFirst();
	while (temp != nullptr)
	{
		if (temp->data.name == str)
		{
			index = temp->data.index;
			break;
		}
		temp = temp->next;
	}
	if (index >= graph->getSize() || index < 0)
	{
		return -1;
	}
	return index;	
}

int OutputManager::hash(const myString& key) const
{
	long long hashValue = 0;
	char c;
	for (int i = 0; i < key.getSize(); i++) {
		c = key[i];
		hashValue = hashValue * 31 + c;
	}
	return hashValue % graph->getHashMap().getSize();
}

int OutputManager::findPath(const myString& srcName, const myString& destName, bool commandTypeOne) const
{
	const int size = graph->getSize();
	const int destIndex = getIndexByName(destName);
	int currentIndex = getIndexByName(srcName);
	int srcIndex = currentIndex;
	int previousIndex = currentIndex;
	int* distances = new int[size];
	int* lastVisitsIndexes = new int[size];
	bool* visited = new bool[size];
	
	for (int i = 0; i < size; i++)
	{
		distances[i] = maxIntValue;
		lastVisitsIndexes[i] = -1;
		visited[i] = false;
	}

	distances[currentIndex] = 0;

	MinHeap heap(graph->getSize());

	while (true)
	{
		myString currentVertex = (*graph)[currentIndex]->getName();
		Node<Connection_T>* neighbour = (*graph)[currentIndex]->getFirstConnection();
		while (neighbour != nullptr)
		{
			if (neighbour->data.dest != nullptr) {
				int tempIndex = getIndexByName(neighbour->data.dest->getName());
				int tempDistance = neighbour->data.weight + distances[currentIndex];
				if (tempDistance < distances[tempIndex] && visited[tempIndex] == false) {
					distances[tempIndex] = tempDistance;
					lastVisitsIndexes[tempIndex] = currentIndex;
					heap.push({ tempDistance,tempIndex,visited[tempIndex] });
				}
			}
			neighbour = neighbour->next;
		}
		visited[currentIndex] = true;
		int newIndex = 0;

		if (heap.isEmpty() || visited[destIndex])
			break;
		HeapItem tmpHeapItem = heap.popMin();
		newIndex = tmpHeapItem.index;
		distances[newIndex] = tmpHeapItem.distance;
		visited[newIndex] = tmpHeapItem.visited;

		previousIndex = currentIndex;
		currentIndex = newIndex;
	}
	int returnDistance = distances[destIndex];

	int x = destIndex;
	int pathIndex = 0;
	myString* pathArray = new myString[size];
	if (commandTypeOne) {
		cout << returnDistance << " ";
		while (lastVisitsIndexes[x] != -1 && lastVisitsIndexes[x] != srcIndex)
		{
			x = lastVisitsIndexes[x];
			pathArray[pathIndex++] = (*graph)[x]->getName();
		}
		while (pathIndex > 0)
		{
			cout << pathArray[--pathIndex];
			cout << " ";
		}
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

	myString src, dest, type;
	int distance;
	for (int i = 0; i < testCount; i++) {
		cin >> src >> dest >> type;
		if (type == "0") {
			distance = findPath(src, dest, false);
			cout << distance << '\n';
		}
		else if (type == "1")
		{
			findPath(src, dest, true);
			cout << '\n';
		}
	}

}


