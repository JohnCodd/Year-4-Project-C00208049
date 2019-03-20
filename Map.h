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
	Map(int tSize, int& turn, ResourceManager& rm);
	~Map() {};
	void loadMap(std::string levelFilePath);
	void update(float dt);
	void render(sf::RenderWindow & window, float tileSize);
	void leftclickMap(sf::Vector2f e);
	void rightclick(sf::Event e);
	void fButton(sf::Vector2f v, ResourceManager& rm);
	void moveSearch(Tile& start, int moves);
	void clearTiles();
	void turnUpkeep();
	bool checkRange(Tile& tile);
	bool checkTile(sf::Vector2f v);
	Tile* getClosest(Tile& t);
	sf::Vector2f convertToKey(sf::Vector2f v);
	sf::Vector2f getMapSize() { return sf::Vector2f(m_sizeX, m_sizeY); }
	sf::FloatRect getBorder() { return m_mapBorder; }
	Tile& getTile(sf::Vector2f v);
	Unit& getUnit(sf::Vector2f v);
	std::list<Unit*> getUnitList() { return m_units; }
private:
	int m_sizeX;
	int m_sizeY;
	int* m_playerTurn;
	float m_tileSize;
	std::map<sf::Vector2f, Tile, VectorComparator> m_tiles;
	std::list<Unit*> m_units;
	sf::Vector2f m_targetLocation;
	Tile startTile;
	Unit* selectedUnit = nullptr;
	sf::Texture m_tileset;
	sf::Texture m_spritesheet;
	sf::Texture m_highlightBorder;
	sf::Texture m_enemyBorder;
	ResourceManager* m_resourceManager;
	sf::FloatRect m_mapBorder;
	sf::RectangleShape m_visualBorder;
};