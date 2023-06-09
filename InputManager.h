#pragma once
#include <iostream>
#include "Config.h"
#include "Vertex.h"

using namespace std;
class InputManager
{
private:
	const int w, h;
	int starCounter;
	bool roadsExist;
	char **map;
	Graph<Vertex>* graph;
private:
	bool isValidCityName(const char c);
	bool isEdgeOfCity(const Coords_T pos);

	myString getCityName(const Coords_T pos);
	myString getCity(const Coords_T pos);

	Vertex*& getVertexByName(const char * str);
	Vertex*& getVertexByPosition(const Coords_T& position);

	void setConnectionsOfVertex(Vertex*& vertex, bool**& visits);

	void loadMap();
	void loadCities();
	void loadConnections();
	void loadPlanes();
	void destroyMap();
	int hash(const char* str) const;
public:
	InputManager(const int w, const int h);
	~InputManager();

	void run();
	Graph<Vertex>* getGraph() const;
};

