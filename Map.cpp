#include "Map.h"
#include "Libraries/nlohmann/json.hpp"
#include <fstream>

// Tiles
#include "Plains.h"
#include "Forest.h"
#include "Sea.h"

// Units
#include "Tank.h"
#include "Bomber.h"


Map::Map()
{
	sizeX = 10;
	sizeY = 10;

	if (!tileset.loadFromFile("./Resources/Tilesets/tileset.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	if (!spritesheet.loadFromFile("./Resources/Sprite Sheets/Unit Spritesheet.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	if (!highlightBorder.loadFromFile("./Resources/Tilesets/BorderHighlight.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	if (!enemyBorder.loadFromFile("./Resources/Tilesets/EnemyHighlight.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	for (int i = 1; i < sizeY; i++)
	{
		for (int j = 1; j < sizeX; j++)
		{
			Plains p = Plains(sf::Vector2f(j,i), tileset, highlightBorder, enemyBorder, tileSize);
			//sf::RectangleShape texture;
			//texture.setTexture(&tileset);
			//texture.setSize(sf::Vector2f(16, 16));
			//texture.setTextureRect(sf::IntRect(16, 16, 16, 16));
			//p.setTexture(&texture);
			tiles[sf::Vector2f(j, i)] = p;
		}
	}
}

Map::Map(int x, int y, int tSize, int& turn, ResourceManager& rm)
{
	sizeX = x;
	sizeY = y;
	tileSize = tSize;
	playerTurn = &turn;
	m_resourceManager = &rm;
	m_resourceManager->loadTexture("tileset", "./Resources/Tilesets/tileset.png");
	m_resourceManager->loadTexture("spritesheet", "./Resources/Sprite Sheets/Unit Spritesheet.png");
	m_resourceManager->loadTexture("highlightBorder", "./Resources/Tilesets/BorderHighlight.png");
	m_resourceManager->loadTexture("enemyBorder", "./Resources/Tilesets/EnemyHighlight.png");
	if (!tileset.loadFromFile("./Resources/Tilesets/tileset.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	//if (!spritesheet.loadFromFile("./Resources/Sprite Sheets/Unit Spritesheet.png"))
	//{
	//	std::string s("Error loading texture");
	//	throw std::exception(s.c_str());
	//}
	//if (!highlightBorder.loadFromFile("./Resources/Tilesets/BorderHighlight.png"))
	//{
	//	std::string s("Error loading texture");
	//	throw std::exception(s.c_str());
	//}
	//if (!enemyBorder.loadFromFile("./Resources/Tilesets/EnemyHighlight.png"))
	//{
	//	std::string s("Error loading texture");
	//	throw std::exception(s.c_str());
	//}
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			if (i < 12)
			{
				Plains p = Plains(sf::Vector2f(j, i), m_resourceManager->getTexture("tileset"), m_resourceManager->getTexture("highlightBorder"), m_resourceManager->getTexture("enemyBorder"), tileSize);
				p.setRect(sf::FloatRect(j * tileSize, i * tileSize, tileSize, tileSize));
				tiles[sf::Vector2f(j, i)] = p;
			}
			else
			{
				Sea s = Sea(sf::Vector2f(j, i), m_resourceManager->getTexture("tileset"), m_resourceManager->getTexture("highlightBorder"), m_resourceManager->getTexture("enemyBorder"), tileSize);
				s.setRect(sf::FloatRect(j * tileSize, i * tileSize, tileSize, tileSize));
				tiles[sf::Vector2f(j, i)] = s;
			}
			sf::Vector2f location = sf::Vector2f(j, i);
			sf::Vector2f newLocation;
			if (i > 0)
			{
				newLocation = sf::Vector2f(j, i - 1);
				tiles[location].addEdge(newLocation, tiles[newLocation]);
			}
			if (j + 1 < sizeX)
			{
				newLocation = sf::Vector2f(j + 1, i);
				tiles[location].addEdge(newLocation, tiles[newLocation]);
			}
			if (i + 1 < sizeY)
			{
				newLocation = sf::Vector2f(j, i + 1);
				tiles[location].addEdge(newLocation, tiles[newLocation]);
			}
			if (j > 0)
			{
				newLocation = sf::Vector2f(j - 1, i);
				tiles[location].addEdge(newLocation, tiles[newLocation]);
			}
		}
	}
	sf::Vector2f location = sf::Vector2f(10, 6);
	tiles[location].setUnit(new Tank(location, 1, m_resourceManager->getTexture("spritesheet"), tileSize));
	location = sf::Vector2f(6, 10);
	tiles[location].setUnit(new Tank(location, 2, m_resourceManager->getTexture("spritesheet"), tileSize));
	location = sf::Vector2f(4, 10);
	tiles[location].setUnit(new Tank(location, 1, m_resourceManager->getTexture("spritesheet"), tileSize));
	location = sf::Vector2f(5, 5);
	tiles[location].setUnit(new Bomber(location, 1, m_resourceManager->getTexture("spritesheet"), tileSize));
}

Map::Map(int tSize, int& turn, ResourceManager& rm)
{
	tileSize = tSize;
	playerTurn = &turn;
	m_resourceManager = &rm;
}

void Map::loadMap(std::string levelFilePath)
{
	std::ifstream i(levelFilePath);
	js::json file;
	i >> file;
	std::cout << file << std::endl;
	auto mapSize = file["Map Size"];
	sizeX = mapSize[0];
	sizeY = mapSize[1];
	m_resourceManager->loadTexture("tileset", "./Resources/Tilesets/tileset.png");
	m_resourceManager->loadTexture("spritesheet", "./Resources/Sprite Sheets/Unit Spritesheet.png");
	m_resourceManager->loadTexture("highlightBorder", "./Resources/Tilesets/BorderHighlight.png");
	m_resourceManager->loadTexture("enemyBorder", "./Resources/Tilesets/EnemyHighlight.png");
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			Plains p = Plains(sf::Vector2f(j, i), m_resourceManager->getTexture("tileset"), m_resourceManager->getTexture("highlightBorder"), m_resourceManager->getTexture("enemyBorder"), tileSize);
			p.setRect(sf::FloatRect(j * tileSize, i * tileSize, tileSize, tileSize));
			tiles[sf::Vector2f(j, i)] = p;
			sf::Vector2f location;
			// May be reimplemented later
			//int t = 0;
			//int fTiles = 0;
			//while (!file["Tiles"][t].is_null())
			//{
			//	while (!file["Tiles"][t]["Forest"][fTiles].is_null())
			//	{
			//		auto position = file["Tiles"][t]["Forest"][fTiles]["Position"];
			//		location = sf::Vector2f(position[0], position[1]);
			//		Forest f = Forest(location, m_resourceManager->getTexture("tileset"), m_resourceManager->getTexture("highlightBorder"), m_resourceManager->getTexture("enemyBorder"), tileSize);
			//		f.setRect(sf::FloatRect(location.x * tileSize, location.y * tileSize, tileSize, tileSize));
			//		tiles[location] = f;
			//		fTiles++;
			//	}
			//	t++;
			//}
			location = sf::Vector2f(j, i);
			sf::Vector2f newLocation;
			if (i > 0)
			{
				newLocation = sf::Vector2f(j, i - 1);
				tiles[location].addEdge(newLocation, tiles[newLocation]);
			}
			if (j + 1 < sizeX)
			{
				newLocation = sf::Vector2f(j + 1, i);
				tiles[location].addEdge(newLocation, tiles[newLocation]);
			}
			if (i + 1 < sizeY)
			{
				newLocation = sf::Vector2f(j, i + 1);
				tiles[location].addEdge(newLocation, tiles[newLocation]);
			}
			if (j > 0)
			{
				newLocation = sf::Vector2f(j - 1, i);
				tiles[location].addEdge(newLocation, tiles[newLocation]);
			}
		}
	}
	sf::Vector2f location;
	int t = 0;
	while (!file["Tiles"][t].is_null())
	{
		int fTiles = 0;
		while (!file["Tiles"][t]["Forest"][fTiles].is_null())
		{
			auto position = file["Tiles"][t]["Forest"][fTiles]["Position"];
			location = sf::Vector2f(position[0], position[1]);
			bool tileFound = false;
			Tile* targetTile = nullptr;
			for (auto &t : tiles)
			{
				if (t.second.getRect().intersects(sf::FloatRect(location.x * tileSize, location.y * tileSize, 2, 2)))
				{
					location = t.first;
					tileFound = true;
					targetTile = &t.second;
				}
			}
			if (tileFound)
			{
				Forest f = Forest(location, m_resourceManager->getTexture("tileset"), m_resourceManager->getTexture("highlightBorder"), m_resourceManager->getTexture("enemyBorder"), tileSize);
				for (auto pair : targetTile->getAdj())
				{
					auto &p = pair.first;
					auto &e = pair.second;
					f.addEdge(p, *e);
				}
				f.setRect(sf::FloatRect(location.x * tileSize, location.y * tileSize, tileSize, tileSize));
				f.setUnit(tiles[location].getUnit());
				tiles[location] = f;
				std::cout << "Forest Tile Created: " << location.x << "," << location.y << std::endl;
			}
			fTiles++;
		}
		int sTiles = 0;
		while (!file["Tiles"][t]["Sea"][sTiles].is_null())
		{
			auto position = file["Tiles"][t]["Sea"][sTiles]["Position"];
			location = sf::Vector2f(position[0], position[1]);
			bool tileFound = false;
			Tile* targetTile = nullptr;
			for (auto &t : tiles)
			{
				if (t.second.getRect().intersects(sf::FloatRect(location.x * tileSize, location.y * tileSize, 2, 2)))
				{
					location = t.first;
					tileFound = true;
					targetTile = &t.second;
				}
			}
			if (tileFound)
			{
				Sea s = Sea(location, m_resourceManager->getTexture("tileset"), m_resourceManager->getTexture("highlightBorder"), m_resourceManager->getTexture("enemyBorder"), tileSize);
				for (auto pair : targetTile->getAdj())
				{
					auto &p = pair.first;
					auto &e = pair.second;
					s.addEdge(p, *e);
				}
				s.setRect(sf::FloatRect(location.x * tileSize, location.y * tileSize, tileSize, tileSize));
				s.setUnit(tiles[location].getUnit());
				tiles[location] = s;
				std::cout << "Sea Tile Created: " << location.x << "," << location.y << std::endl;
			}
			sTiles++;
		}
		t++;
	}
	int u = 0;
	while (!file["Units"][u].is_null())
	{
		int tankNo = 0;
		while (!file["Units"][u]["Tank"][tankNo].is_null())
		{
			auto position = file["Units"][u]["Tank"][tankNo]["Position"];
			auto playerNo = file["Units"][u]["Tank"][tankNo]["Player"].get<int>();
			location = sf::Vector2f(position[0], position[1]);
			tiles[location].setUnit(new Tank(location, playerNo, m_resourceManager->getTexture("spritesheet"), tileSize));
			tankNo++;
		}
		int bomberNo = 0;
		while (!file["Units"][u]["Bomber"][bomberNo].is_null())
		{
			auto position = file["Units"][u]["Bomber"][bomberNo]["Position"];
			auto playerNo = file["Units"][u]["Bomber"][bomberNo]["Player"].get<int>();
			location = sf::Vector2f(position[0], position[1]);
			tiles[location].setUnit(new Bomber(location, playerNo, m_resourceManager->getTexture("spritesheet"), tileSize));
			bomberNo++;
		}
		u++;
	}
}

void Map::render(sf::RenderWindow & window, float tileSize)
{
	for (auto &t : tiles)
	{
		t.second.render(window);
		if (t.second.getUnit())
		{
			t.second.getUnit()->render(window);
		}		
	}
}

void Map::leftclickMap(sf::Vector2f v)
{
	sf::Vector2f mousePosition = sf::Vector2f(floor(v.x / tileSize), floor(v.y / tileSize));
	sf::Vector2f tileLocation;
	Tile* targetTile = nullptr;
	for (auto &t : tiles)
	{
		if (t.second.getRect().intersects(sf::FloatRect(v.x, v.y, 2, 2)))
		{
			tileLocation = t.first;
			targetTile = &t.second;
		}
	}
	if (targetTile)
	{
		if (targetTile->getUnit() != nullptr)
		{
			if (targetTile->getUnit()->getTurn())
			{
				//Checks if there is no actively selected unit
				if (selectedUnit == nullptr)
				{
					if (targetTile->getUnit()->getOwner() == *playerTurn)
					{
						selectedUnit = targetTile->getUnit();
						moveSearch(tiles[tileLocation], tiles[tileLocation].getUnit()->getRemainingMoves());
						//expandtile(sf::Vector2f(static_cast<int>((mousePosition.x) + 1), static_cast<int>((mousePosition.y) + 1)), units[tileLocation].getMoves());
						std::cout << "Clicked: " << tileLocation.x << ", " << tileLocation.y << std::endl;
					}
				}
				//Checks if the targeted unit is an enemy and is within range of the selected unit
				else if (tiles[tileLocation].getUnit()->getOwner() != selectedUnit->getOwner() && checkRange(tiles[tileLocation]))
				{
					Unit* targetUnit = tiles[tileLocation].getUnit();
					Tile* closest = getClosest(tiles[tileLocation]);
					//Damage the units
					targetUnit->damage(selectedUnit->getPower() + 10 - targetTile->getDefense());
					if (targetUnit->getHealth() <= 0)
					{
						tiles[targetUnit->getLocation()].setUnit(nullptr);
						targetUnit = nullptr;
					}
					if (targetUnit)
					{
						selectedUnit->damage(targetUnit->getPower() - closest->getDefense());
						if (selectedUnit->getHealth() <= 0)
						{
							tiles[selectedUnit->getLocation()].setUnit(nullptr);
							selectedUnit = nullptr;
						}
					}
					if (&tiles[selectedUnit->getLocation()] != closest && targetUnit)
					{
						Unit movingUnit = *selectedUnit;
						//auto result = std::find_if(tiles.begin(), tiles.end(), [&](std::pair<sf::Vector2f, Tile> p)
						//{
						//	//return p.second == *closest;
						//});

						movingUnit.setLocation(targetLocation);
						closest->setUnit(new Unit(movingUnit));
						tiles[selectedUnit->getLocation()].setUnit(nullptr);
					}
					selectedUnit = nullptr;
					tiles[targetLocation].getUnit()->moveTaken(tiles[targetLocation].getSCost());
					tiles[targetLocation].getUnit()->setTurn(false);
					clearTiles();
				}
			}
		}
		else if (tiles[tileLocation].getHighlighted() == true)
		{
			Unit movingUnit = *selectedUnit;
			movingUnit.setLocation(sf::Vector2f(mousePosition.x, mousePosition.y));
			tiles[tileLocation].setUnit(new Unit(movingUnit));
			tiles[selectedUnit->getLocation()].setUnit(nullptr);
			selectedUnit = nullptr;
			tiles[tileLocation].getUnit()->moveTaken(tiles[tileLocation].getSCost());
			clearTiles();
		}
	}
}

void Map::rightclick(sf::Event e)
{
	selectedUnit = nullptr;
	clearTiles();
}

void Map::moveSearch(Tile& start, int moves)
{
	//BFS Algorithim
	std::list<Tile*> queue;
	for (auto &tile : tiles)
	{
		tile.second.setSCost(0);
		tile.second.setVisited(false);
	}
	start.setVisited(true);
	start.setSCost(moves);
	start.setHighlight(true);
	queue.push_back(&start);

	while (!queue.empty())
	{
		for (auto &pair : queue.front()->getAdj())
		{
			auto & e = pair.second;
			if (pair.first == sf::Vector2f(4, 11))
			{
				std::cout << "Test" << std::endl;
			}
			int movesRemaining = queue.front()->getSCost() - start.getUnit()->getChartCost(e->getType());
			if (movesRemaining >= 0)
			{
				if (movesRemaining > e->getSCost())
				{
					e->setVisited(false);
				}
				if (e->getUnit() != nullptr)
				{
					//Check if the unit is friendly: if true it can pass through
					if (e->getVisited() == false && e->getUnit()->getOwner() == start.getUnit()->getOwner())
					{
						e->setSCost(movesRemaining);
						e->setVisited(true);
						e->setHighlight(true);
						e->setPrevious(*queue.front());
						queue.push_back(e);
					}
					else
					{
						e->setEnemy(true);
					}
				}
				else
				{
					if (e->getVisited() == false)
					{
						e->setSCost(movesRemaining);
						e->setVisited(true);
						e->setHighlight(true);
						e->setPrevious(*queue.front());
						queue.push_back(e);
					}
				}
			}
			if (checkRange(*e))
			{
				if (e->getUnit() != nullptr)
				{
					//Check if the unit is friendly: if true it can pass through
					if (e->getVisited() == false && e->getUnit()->getOwner() == start.getUnit()->getOwner())
					{
					}
					else
					{
						e->setEnemy(true);
					}
				}
			}
			if (pair.first == sf::Vector2f(4, 10))
			{
				std::cout << "Test" << std::endl;
			}
		}
		queue.pop_front();
	}
}

void Map::clearTiles()
{
	for (auto const& a : tiles)
	{
		tiles[a.first].setHighlight(false);
		tiles[a.first].setEnemy(false);
	}
}

void Map::turnUpkeep()
{
	for (auto const& a : tiles)
	{
		auto t = a.second;
		if (t.getUnit())
		{
			if (t.getUnit()->getOwner() == *playerTurn)
			{
				t.getUnit()->upkeep();
			}
		}
	}
}

bool Map::checkRange(Tile & tile)
{
	for (auto& pair : tile.getAdj())
	{
		auto t = pair.second;
		if (t->getHighlighted())
		{
			return true;
		}
	}
	return false;
}

bool Map::checkTile(sf::Vector2f v)
{
	if (&tiles[v] != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Map::fButton(sf::Vector2f v, ResourceManager& rm)
{
	sf::Vector2f mousePosition = convertToKey(v);
	sf::Vector2f tileLocation;
	bool tileFound = false;
	Tile* targetTile = nullptr;
	for (auto &t : tiles)
	{
		if (t.second.getRect().intersects(sf::FloatRect(v.x, v.y, 2, 2)))
		{
			tileLocation = t.first;
			tileFound = true;
			targetTile = &t.second;
		}
	}
	if (tileFound)
	{
		Forest f = Forest(tileLocation, rm.getTexture("tileset"), rm.getTexture("highlightBorder"), rm.getTexture("enemyBorder"), tileSize);
		for (auto pair : targetTile->getAdj())
		{
			auto &p = pair.first;
			auto &e = pair.second;
			f.addEdge(p, *e);
		}
		f.setRect(sf::FloatRect(tileLocation.x * tileSize, tileLocation.y * tileSize, tileSize, tileSize));
		f.setUnit(tiles[tileLocation].getUnit());
		tiles[tileLocation] = f;
	}
}

Tile* Map::getClosest(Tile& t)
{
	Tile* highest = nullptr;
	int cost = 0;
	for (auto pair : t.getAdj())
	{
		auto a = pair.second;
		if (a->getHighlighted())
		{
			if (highest)
			{
				if (highest->getSCost() < a->getSCost())
				{
					highest = a;
					targetLocation = pair.first;
					cost = highest->getSCost();
				}
			}
			else
			{
				highest = a;
				targetLocation = pair.first;
				cost = highest->getSCost();
			}
		}
	}
	return highest;
}

sf::Vector2f Map::convertToKey(sf::Vector2f v)
{
	return sf::Vector2f(floor(v.x / tileSize), floor(v.y / tileSize));
}

Tile & Map::getTile(sf::Vector2f v)
{
	return tiles[v];
}

Unit & Map::getUnit(sf::Vector2f v)
{
	return *tiles[v].getUnit();
}
