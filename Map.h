#pragma once
#include "Plains.h"
#include "Forest.h"
#include "Tank.h"
#include <map>
struct VectorComparator
{
	bool operator() (sf::Vector2f lhs, sf::Vector2f rhs) const
	{
		return std::tie(lhs.x, rhs.y) < std::tie(rhs.x, lhs.y);
	}
};
class Map
{
public:
	Map();
	Map(int sizeX, int sizeY);
	~Map() {};
	void render(sf::RenderWindow & window);
	void leftclick(sf::Event e);
	void rightclick(sf::Event e);
	void fButton(sf::Vector2i v);
	void expandtile(sf::Vector2f location, int moves);
	void moveSearch(Tile& start, int moves);
	void clearTiles();
	bool checkRange(Tile& tile);
	Tile* getClosest(Tile& t);
private:
	int sizeX;
	int sizeY;
	std::map<sf::Vector2f, Tile, VectorComparator> tiles;
	std::map<sf::Vector2f, Unit, VectorComparator> units;
	sf::Vector2f targetLocation;
	Unit* selectedUnit = nullptr;
	sf::Texture tileset;
	sf::Texture spritesheet;
	sf::Texture highlightBorder;
};