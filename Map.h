#pragma once
#include "Tile.h"
#include "Unit.h"
#include <map>
#include "ResourceManager.h"
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
	Map(int sizeX, int sizeY, int tSize, int& turn, ResourceManager& rm);
	~Map() {};
	void render(sf::RenderWindow & window, float tileSize);
	void leftclickMap(sf::Vector2f e);
	void rightclick(sf::Event e);
	void fButton(sf::Vector2f v, ResourceManager& rm);
	void moveSearch(Tile& start, int moves);
	void clearTiles();
	bool checkRange(Tile& tile);
	bool checkTile(sf::Vector2f v);
	Tile* getClosest(Tile& t);
	sf::Vector2f convertToKey(sf::Vector2f v);
	Tile& getTile(sf::Vector2f v);
	Unit& getUnit(sf::Vector2f v);
private:
	int sizeX;
	int sizeY;
	int* playerTurn;
	float tileSize;
	std::map<sf::Vector2f, Tile, VectorComparator> tiles;
	std::map<sf::Vector2f, Unit, VectorComparator> units;
	sf::Vector2f targetLocation;
	Unit* selectedUnit = nullptr;
	sf::Texture tileset;
	sf::Texture spritesheet;
	sf::Texture highlightBorder;
	sf::Texture enemyBorder;
};