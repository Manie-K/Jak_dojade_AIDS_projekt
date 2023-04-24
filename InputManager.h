#pragma once
#include <iostream>
#include "Config.h"
#include "Graph.h"
#include "Vertex.h"

using namespace std;

class InputManager
{
private:
	const int w, h;
	int starCounter;
	char **map;
	Graph<Vertex>* graph;
private:
	bool isValidCityName(const char c)
	{
		return !(c == STAR_CHAR || c == ROAD_CHAR || c == EMPTY_CHAR);
	}
	bool isEdgeOfCity(const Coords_T pos)
	{
		return !(isValidCityName(map[pos.y][pos.x - 1]) && isValidCityName(map[pos.y][pos.x + 1]));
	}

	myString getCityName(const Coords_T pos)
	{
		myString temp;
		int x = pos.x;
		const int y = pos.y;
		
		while (x > 0 && isValidCityName(map[y][x-1]))
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
	myString getCity(const Coords_T pos)
	{
		int x = pos.x;
		int y = pos.y;
		
		//top
		if (y > 0 && isValidCityName(map[y - 1][x]) && isEdgeOfCity({ x,y - 1 }))
		{
			return getCityName({ x,y - 1 });
		}
		//bottom
		if (y < h -1 && isValidCityName(map[y + 1][x]) && isEdgeOfCity({ x,y + 1 }))
		{
			return getCityName({ x,y + 1 });
		}
		//right
		if (x < w-1 && isValidCityName(map[y][x+1]) && isEdgeOfCity({ x+1,y }))
		{
			return getCityName({ x+1,y });
		}
		//left
		if (x > 0 && isValidCityName(map[y][x-1]) && isEdgeOfCity({ x-1,y }))
		{
			return getCityName({ x-1,y });
		}
		//topLeft
		if (x > 0 && y > 0 && isValidCityName(map[y - 1][x - 1]) && isEdgeOfCity({ x - 1,y - 1 }))
		{
			return getCityName({ x - 1,y - 1 });
		}
		//topRight
		if (x < w-1 && y > 0 && isValidCityName(map[y - 1][x + 1]) && isEdgeOfCity({ x - 1,y + 1 }))
		{
			return getCityName({ x + 1,y - 1 });
		}

		//bottomRight
		if (x <w-1 && y <h-1 && isValidCityName(map[y + 1][x + 1]) && isEdgeOfCity({ x + 1,y + 1 }))
		{
			return getCityName({ x + 1,y + 1 });
		}

		//topLeft
		if (x > 0 && y < h-1 && isValidCityName(map[y + 1][x - 1]) && isEdgeOfCity({ x - 1,y + 1 }))
		{
			return getCityName({ x - 1,y + 1 });
		}
	}

	Vertex*& getVertexByName(const myString& str)
	{
		for (int i = 0; i < graph->getSize(); i++)
		{
			if ((*graph)[i]->getName() == str)
				return (*graph)[i];
		}
	}
	Vertex*& getVertexByPosition(const Coords_T& position)
	{
		for (int i = 0; i < graph->getSize(); i++)
		{
			if ((*graph)[i]->getPos() == position)
				return (*graph)[i];
		}
	}

	void getConnection(Vertex*& vertex, bool** visits)
	{
		typedef struct {
			Coords_T pos;
			int distance;
		} CoordsAndDistance;

		const int x= vertex->getPos().x;
		const int y= vertex->getPos().y;
		Coords_T pos;
		Queue<CoordsAndDistance> path;
		int distance = 0;

		path.push({{x,y},distance });
		
		visits[pos.y][pos.x] = true;
		

		while (path.getSize() > 0){
			CoordsAndDistance temp = path.pop();
			distance = temp.distance;
			pos = temp.pos;
			
			if (map[pos.y][pos.x] == STAR_CHAR)
			{
				Vertex* found = getVertexByPosition(pos);
				vertex->addConnection(found, distance);
				continue;
			}
			distance++;

			pos.x++;
			if (visits[pos.y][pos.x] == false && map[pos.y][pos.x] == ROAD_CHAR || map[pos.y][pos.x] == STAR_CHAR)
			{
				visits[pos.y][pos.x] = true;
				path.push({ pos,distance });
			}
			pos.x-=2;
			if (visits[pos.y][pos.x] == false && map[pos.y][pos.x] == ROAD_CHAR || map[pos.y][pos.x] == STAR_CHAR)
			{
				visits[pos.y][pos.x] = true;
				path.push({ pos,distance });
			}
			pos.x++;
			pos.y++;
			if (visits[pos.y][pos.x] == false && map[pos.y][pos.x] == ROAD_CHAR || map[pos.y][pos.x] == STAR_CHAR)
			{
				visits[pos.y][pos.x] = true;
				path.push({ pos,distance });
			}
			pos.y -= 2;
			if (visits[pos.y][pos.x] == false && map[pos.y][pos.x] == ROAD_CHAR || map[pos.y][pos.x] == STAR_CHAR)
			{
				visits[pos.y][pos.x] = true;
				path.push({ pos,distance });
			}
		} 
	}
public:
	InputManager(const int w, const int h) : w(w), h(h), starCounter(0), graph(nullptr)
	{
		map = new char* [h];
		for (int y = 0; y < h; y++)
		{
			map[y] = new char [w];
		}
	};
	~InputManager()
	{
		delete graph;
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				delete map[y];
				map[y] = nullptr;
			}
		}
		delete map;
		map = nullptr;
	}

	Graph<Vertex>* getGraph() const { return graph; }

	void loadMap() 
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
			}
		}
		graph = new Graph<Vertex>(starCounter);
	}
	void loadCities()
	{
		int citiesCounter = 0;
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				if (map[y][x] == STAR_CHAR)
				{
					Vertex *temp = new Vertex;
					temp->setPos({ x,y });
					temp->setName(getCity(temp->getPos()));
					(*graph)[citiesCounter] = temp;
					citiesCounter++;
				}
			}
		}
	}

	void loadConnections()
	{
		bool** visitArray = new bool*[h];
		for (int i = 0; i < w; i++) {
			visitArray[i] = new bool[w];
			for (int j = 0; j < h; j++)
			{
				visitArray[j][i] = false;
			}
		}

		for (int i = 0; i < graph->getSize(); i++)
		{
			getConnection((*graph)[i], visitArray);
		}

		for (int i = 0; i < w; i++) {
			delete visitArray[i];
		}
		delete visitArray;
	}

};

