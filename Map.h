#pragma once
#include "Plains.h"
#include "Tank.h"
#include <map>
class Map
{
public:
	Map();
	Map(int sizeX, int sizeY);
	~Map() {};
	void render(sf::RenderWindow & window);
	void leftclick(sf::Event e);
private:
	int sizeX;
	int sizeY;
	std::map<std::string, Tile> tiles;
	std::map<std::string, Unit> units;
	sf::Texture tileset;
	sf::Texture spritesheet;
};