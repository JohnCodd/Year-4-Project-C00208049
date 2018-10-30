#pragma once
#include "Plains.h"
#include <map>
class Map
{
public:
	Map();
	Map(int sizeX, int sizeY);
	~Map() {};
	void render(sf::RenderWindow & window);
private:
	int sizeX;
	int sizeY;
	std::map<std::string, Tile> tiles;
};