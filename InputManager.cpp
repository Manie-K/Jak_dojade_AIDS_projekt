#include "InputManager.h"

InputManager::InputManager(const int w, const int h) : w(w), h(h), starCounter(0),hashtagExist(false), graph(nullptr)
{
	map = new char* [h];
	for (int y = 0; y < h; y++)
	{
		map[y] = new char[w];
	}
};
InputManager::~InputManager()
{
	delete graph;
}

bool InputManager::isValidCityName(const char c)
{
	return !(c == STAR_CHAR || c == ROAD_CHAR || c == EMPTY_CHAR);
}
bool InputManager::isEdgeOfCity(const Coords_T pos)
{
	if (pos.y >= 0 && pos.y < h) {
		if (pos.x - 1 >= 0 && pos.x + 1 < w)
			return !(isValidCityName(map[pos.y][pos.x - 1]) && isValidCityName(map[pos.y][pos.x + 1]));
		else
			return true;
	}
	return false;
}

int InputManager::hash(const myString& key) const
{
	long long hashValue = 0;
	char c;
	for (int i = 0; i < key.getSize();i++) {
		c = key[i];
		hashValue = hashValue * 31 + c;
	}
	return hashValue % graph->getHashMap().getSize();
}

Vertex*& InputManager::getVertexByName(const myString& str)
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
	return (*graph)[index];
}
Vertex*& InputManager::getVertexByPosition(const Coords_T& position)
{
	int index = 0;
	for (int i = 0; i < graph->getSize(); i++)
	{
		if ((*graph)[i]->getPos() == position)
		{
			index = i;
			break;
		}
	}
	return (*graph)[index];
}

myString InputManager::getCityName(const Coords_T pos)
{
	int x = pos.x;
	const int y = pos.y;
	myString temp;

	while (x > 0 && isValidCityName(map[y][x - 1]))
	{
		x--;
	}
	while (x < w && isValidCityName(map[y][x]))
	{
		temp.pushCharAtEnd(map[y][x]);
		x++;
	}

	return temp;
}
myString InputManager::getCity(const Coords_T pos)
{
	int x = pos.x;
	int y = pos.y;

	//top
	if (y > 0 && isValidCityName(map[y - 1][x]) && isEdgeOfCity({ x,y - 1 }))
	{
		return getCityName({ x,y - 1 });
	}
	//bottom
	if (y < h - 1 && isValidCityName(map[y + 1][x]) && isEdgeOfCity({ x,y + 1 }))
	{
		return getCityName({ x,y + 1 });
	}
	//right
	if (x < w - 1 && isValidCityName(map[y][x + 1]) && isEdgeOfCity({ x + 1,y }))
	{
		return getCityName({ x + 1,y });
	}
	//left
	if (x > 0 && isValidCityName(map[y][x - 1]) && isEdgeOfCity({ x - 1,y }))
	{
		return getCityName({ x - 1,y });
	}
	//topLeft
	if (x > 0 && y > 0 && isValidCityName(map[y - 1][x - 1]) && isEdgeOfCity({ x - 1,y - 1 }))
	{
		return getCityName({ x - 1,y - 1 });
	}
	//topRight
	if (x < w - 1 && y > 0 && isValidCityName(map[y - 1][x + 1]) && isEdgeOfCity({ x + 1,y - 1 }))
	{
		return getCityName({ x + 1,y - 1 });
	}

	//bottomRight
	if (x < w - 1 && y < h - 1 && isValidCityName(map[y + 1][x + 1]) && isEdgeOfCity({ x + 1,y + 1 }))
	{
		return getCityName({ x + 1,y + 1 });
	}

	//topLeft
	if (x > 0 && y < h - 1 && isValidCityName(map[y + 1][x - 1]) && isEdgeOfCity({ x - 1,y + 1 }))
	{
		return getCityName({ x - 1,y + 1 });
	}
	return "";
}


void InputManager::setConnectionsOfVertex(Vertex*& vertex, bool**& visits)
{
	typedef struct {
		Coords_T pos;
		int distance;
	} CoordsAndDistance;

	const int x = vertex->getPos().x, y = vertex->getPos().y;
	Coords_T pos = { x,y };
	Queue<CoordsAndDistance> path;
	int distance = 0;

	path.push({ {x,y},distance });

	visits[pos.y][pos.x] = true;

	while (path.getSize() > 0) 
	{
		CoordsAndDistance temp = path.pop();
		distance = temp.distance;
		pos = temp.pos;
		
		if (map[pos.y][pos.x] == STAR_CHAR && (pos.y != y || pos.x != x))
		{
			Vertex* found = getVertexByPosition(pos);
			vertex->addConnection(found, distance);
			continue;
		}
		distance++;

		pos.x++;
		if (pos.x < w && visits[pos.y][pos.x] == false && (map[pos.y][pos.x] == ROAD_CHAR || map[pos.y][pos.x] == STAR_CHAR))
		{
			visits[pos.y][pos.x] = true;
			path.push({ pos,distance });
		}
		pos.x -= 2;
		if (pos.x >= 0 && visits[pos.y][pos.x] == false && (map[pos.y][pos.x] == ROAD_CHAR || map[pos.y][pos.x] == STAR_CHAR))
		{
			visits[pos.y][pos.x] = true;
			path.push({ pos,distance });
		}
		pos.x++;
		pos.y++;
		if (pos.y < h && visits[pos.y][pos.x] == false && (map[pos.y][pos.x] == ROAD_CHAR || map[pos.y][pos.x] == STAR_CHAR))
		{
			visits[pos.y][pos.x] = true;
			path.push({ pos,distance });
		}
		pos.y -= 2;
		if (pos.y >= 0 && visits[pos.y][pos.x] == false && (map[pos.y][pos.x] == ROAD_CHAR || map[pos.y][pos.x] == STAR_CHAR))
		{
			visits[pos.y][pos.x] = true;
			path.push({ pos,distance });
		}
	}
}

void InputManager::loadMap()
{
	char temp;
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			cin >> temp;
			map[y][x] = temp;
			if (temp == STAR_CHAR)
				starCounter++;
			else if (temp == ROAD_CHAR)
				hashtagExist = true;
		}
	}
	graph = new Graph<Vertex>(starCounter);
}
void InputManager::loadCities()
{
	int citiesCount = 0, index = 0;
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (map[y][x] == STAR_CHAR)
			{
				Vertex* temp = new Vertex;
				temp->setPos({ x,y });
				temp->setName(getCity(temp->getPos()));

				const myString name = temp->getName();
				index = hash(name);

				HashMapItem tempItem(&name);
				tempItem.index = citiesCount;
				Node<HashMapItem>* tempHashItem = new Node<HashMapItem>(tempItem);
				
				(*graph)[citiesCount++] = temp;
				graph->getHashMap()[index].addFirst(*tempHashItem);
			}
		}
	}
}
void InputManager::loadConnections()
{
	if (!hashtagExist)
		return;
	bool** visitArray = new bool* [h];
	for (int i = 0; i < h; i++) {
		visitArray[i] = new bool[w];
	}

	for (int i = 0; i < graph->getSize(); i++)
	{
		for (int y = 0; y < h; y++)
		{
			memset(visitArray[y], false, w);
		}
		setConnectionsOfVertex((*graph)[i], visitArray);
	}
	for (int i = 0; i < h; i++) {
		delete[]visitArray[i];
	}
	delete[]visitArray;
}
void InputManager::loadPlanes()
{
	int howManyPlanes;
	cin >> howManyPlanes;

	myString src, dest;
	int distance;

	for (int i = 0; i < howManyPlanes; i++)
	{
		cin >> src >> dest >> distance;
		getVertexByName(src)->addConnection(getVertexByName(dest), distance);
	}
}

Graph<Vertex>* InputManager::getGraph() const 
{ 
	return graph; 
}

void InputManager::run()
{
	loadMap();
	loadCities();
	loadConnections();
	loadPlanes();
	destroyMap();
}

void InputManager::destroyMap()
{
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			delete[] map[y];
			map[y] = nullptr;
		}
	}
	delete[]map;
	map = nullptr;
}