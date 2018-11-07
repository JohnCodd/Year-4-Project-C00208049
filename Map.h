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
	void rightclick(sf::Event e);
	void expandtile(sf::Vector2f location, int moves);
	void clearTiles();
private:
	int sizeX;
	int sizeY;
	std::map<std::string, Tile> tiles;
	std::map<std::string, Unit> units;
	std::string selectedUnit;
	sf::Texture tileset;
	sf::Texture spritesheet;
};