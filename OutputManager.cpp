#include "OutputManager.h"

int OutputManager::getIndexByName(const myString& str) const
{
	int index = 0;
	int hashIndex = hash(str.getCharPointer());
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

int OutputManager::hash(const char* key) const
{
	long long hashValue = 0;
	char c;
	for (int i = 0; i < (int)strlen(key)+1; i++) {
		c = key[i];
		hashValue = hashValue * 31 + c;
	}
	return hashValue % graph->getHashMap().getSize();
}

void OutputManager::resetDjikstraArrays(int* distances, int* lastVisits, bool* visited, const int size) const
{
	for (int i = 0; i < size; i++){
		distances[i] = maxIntValue;
		lastVisits[i] = -1;
		visited[i] = false;
	}
}

void OutputManager::commandTypeOneDisplay(int retDist, int* lastVis, int dInd, int sInd, int size) const
{
	int x = dInd, pathIndex = 0;
	myString* pathArray = new myString[size];
	cout << retDist << " ";
	while (lastVis[x] != -1 && lastVis[x] != sInd) {
		x = lastVis[x];
		pathArray[pathIndex++] = (*graph)[x]->getName();
	}
	while (pathIndex > 0) {
		cout << pathArray[--pathIndex];
		cout << " ";
	}
	delete[] pathArray;
}

void OutputManager::djikstraUpdate(MinHeap* heap, int* newIndex, int* distances, bool* visited, int* prevInd, int* currInd) const
{
	HeapItem tmpHeapItem = heap->popMin();
	*newIndex = tmpHeapItem.index;
	distances[*newIndex] = tmpHeapItem.distance;
	visited[*newIndex] = tmpHeapItem.visited;

	*prevInd = *currInd;
	*currInd = *newIndex;
}

int OutputManager::findPath(const myString& srcName, const myString& destName, bool commandTypeOne) const
{
	const int size = graph->getSize();
	const int destIndex = getIndexByName(destName);
	int currentIndex = getIndexByName(srcName);
	int srcIndex = currentIndex, previousIndex = currentIndex, newIndex = 0;
	int *distances = new int[size], *lastVisitsIndexes = new int[size];
	bool* visited = new bool[size];
	
	resetDjikstraArrays(distances, lastVisitsIndexes, visited, size);
	distances[currentIndex] = 0;
	MinHeap heap(graph->getSize());

	while (true){
		Node<Connection_T>* neighbour = (*graph)[currentIndex]->getFirstConnection();
		
		while (neighbour != nullptr){
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

		if (heap.isEmpty() || visited[destIndex])
			break;
		djikstraUpdate(&heap, &newIndex, distances, visited, &previousIndex, &currentIndex);
	}
	int returnDistance = distances[destIndex];
	
	if (commandTypeOne)
		commandTypeOneDisplay(returnDistance, lastVisitsIndexes, destIndex, srcIndex, size);
	delete[] distances;
	delete[] visited;
	delete[] lastVisitsIndexes;

	return returnDistance;
}

OutputManager::OutputManager(const int tests, Graph<Vertex>* g) :testCount(tests), graph(g), maxIntValue(INT_MAX) {}
OutputManager::~OutputManager() {}

void OutputManager::run() const
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


