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
#include "Heli.h"
#include "AntiAir.h"


Map::Map()
{
	m_sizeX = 10;
	m_sizeY = 10;

	if (!m_tileset.loadFromFile("./Resources/Tilesets/tileset.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	if (!m_spritesheet.loadFromFile("./Resources/Sprite Sheets/Unit Spritesheet.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	if (!m_highlightBorder.loadFromFile("./Resources/Tilesets/BorderHighlight.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	if (!m_enemyBorder.loadFromFile("./Resources/Tilesets/EnemyHighlight.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	for (int i = 1; i < m_sizeY; i++)
	{
		for (int j = 1; j < m_sizeX; j++)
		{
			Plains p = Plains(sf::Vector2f(j,i), m_tileset, m_highlightBorder, m_enemyBorder, m_tileSize);
			//sf::RectangleShape texture;
			//texture.setTexture(&tileset);
			//texture.setSize(sf::Vector2f(16, 16));
			//texture.setTextureRect(sf::IntRect(16, 16, 16, 16));
			//p.setTexture(&texture);
			m_tiles[sf::Vector2f(j, i)] = p;
		}
	}
}

Map::Map(int x, int y, int tSize, int& turn, ResourceManager& rm)
{
	m_sizeX = x;
	m_sizeY = y;
	m_tileSize = tSize;
	m_playerTurn = &turn;
	m_resourceManager = &rm;
	m_resourceManager->loadTexture("tileset", "./Resources/Tilesets/tileset.png");
	m_resourceManager->loadTexture("spritesheet", "./Resources/Sprite Sheets/Unit Spritesheet.png");
	m_resourceManager->loadTexture("highlightBorder", "./Resources/Tilesets/BorderHighlight.png");
	m_resourceManager->loadTexture("enemyBorder", "./Resources/Tilesets/EnemyHighlight.png");
	if (!m_tileset.loadFromFile("./Resources/Tilesets/tileset.png"))
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
	for (int i = 0; i < m_sizeY; i++)
	{
		for (int j = 0; j < m_sizeX; j++)
		{
			if (i < 12)
			{
				Plains p = Plains(sf::Vector2f(j, i), m_resourceManager->getTexture("tileset"), m_resourceManager->getTexture("highlightBorder"), m_resourceManager->getTexture("enemyBorder"), m_tileSize);
				p.setRect(sf::FloatRect(j * m_tileSize, i * m_tileSize, m_tileSize, m_tileSize));
				m_tiles[sf::Vector2f(j, i)] = p;
			}
			else
			{
				Sea s = Sea(sf::Vector2f(j, i), m_resourceManager->getTexture("tileset"), m_resourceManager->getTexture("highlightBorder"), m_resourceManager->getTexture("enemyBorder"), m_tileSize);
				s.setRect(sf::FloatRect(j * m_tileSize, i * m_tileSize, m_tileSize, m_tileSize));
				m_tiles[sf::Vector2f(j, i)] = s;
			}
			sf::Vector2f location = sf::Vector2f(j, i);
			sf::Vector2f newLocation;
			if (i > 0)
			{
				newLocation = sf::Vector2f(j, i - 1);
				m_tiles[location].addEdge(newLocation, m_tiles[newLocation]);
			}
			if (j + 1 < m_sizeX)
			{
				newLocation = sf::Vector2f(j + 1, i);
				m_tiles[location].addEdge(newLocation, m_tiles[newLocation]);
			}
			if (i + 1 < m_sizeY)
			{
				newLocation = sf::Vector2f(j, i + 1);
				m_tiles[location].addEdge(newLocation, m_tiles[newLocation]);
			}
			if (j > 0)
			{
				newLocation = sf::Vector2f(j - 1, i);
				m_tiles[location].addEdge(newLocation, m_tiles[newLocation]);
			}
		}
	}
	sf::Vector2f location = sf::Vector2f(10, 6);
	m_tiles[location].setUnit(new Tank(location, 1, m_resourceManager->getTexture("spritesheet"), m_tileSize));
	location = sf::Vector2f(6, 10);
	m_tiles[location].setUnit(new Tank(location, 2, m_resourceManager->getTexture("spritesheet"), m_tileSize));
	location = sf::Vector2f(4, 10);
	m_tiles[location].setUnit(new Tank(location, 1, m_resourceManager->getTexture("spritesheet"), m_tileSize));
	location = sf::Vector2f(5, 5);
	m_tiles[location].setUnit(new Bomber(location, 1, m_resourceManager->getTexture("spritesheet"), m_tileSize));
}

Map::Map(int tSize, int& turn, ResourceManager& rm)
{
	m_tileSize = tSize;
	m_playerTurn = &turn;
	m_resourceManager = &rm;
}

void Map::loadMap(std::string levelFilePath)
{
	std::ifstream i(levelFilePath);
	js::json file;
	i >> file;
	std::cout << file << std::endl;
	auto mapSize = file["Map Size"];
	m_sizeX = mapSize[0];
	m_sizeY = mapSize[1];
	m_mapBorder = sf::FloatRect(0, 0, m_sizeX * m_tileSize, m_sizeY * m_tileSize);
	m_visualBorder.setPosition(0, 0);
	m_visualBorder.setSize(sf::Vector2f(m_mapBorder.width, m_mapBorder.height));
	m_visualBorder.setOutlineColor(sf::Color(255, 102, 0));
	m_visualBorder.setOutlineThickness(5);
	m_visualBorder.setFillColor(sf::Color::Transparent);
	m_resourceManager->loadTexture("tileset", "./Resources/Tilesets/tileset.png");
	m_resourceManager->loadTexture("spritesheet", "./Resources/Sprite Sheets/Unit Spritesheet.png");
	m_resourceManager->loadTexture("highlightBorder", "./Resources/Tilesets/BorderHighlight.png");
	m_resourceManager->loadTexture("enemyBorder", "./Resources/Tilesets/EnemyHighlight.png");
	for (int i = 0; i < m_sizeY; i++)
	{
		for (int j = 0; j < m_sizeX; j++)
		{
			Plains p = Plains(sf::Vector2f(j, i), m_resourceManager->getTexture("tileset"), m_resourceManager->getTexture("highlightBorder"), m_resourceManager->getTexture("enemyBorder"), m_tileSize);
			p.setRect(sf::FloatRect(j * m_tileSize, i * m_tileSize, m_tileSize, m_tileSize));
			m_tiles[sf::Vector2f(j, i)] = p;
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
				m_tiles[location].addEdge(newLocation, m_tiles[newLocation]);
			}
			if (j + 1 < m_sizeX)
			{
				newLocation = sf::Vector2f(j + 1, i);
				m_tiles[location].addEdge(newLocation, m_tiles[newLocation]);
			}
			if (i + 1 < m_sizeY)
			{
				newLocation = sf::Vector2f(j, i + 1);
				m_tiles[location].addEdge(newLocation, m_tiles[newLocation]);
			}
			if (j > 0)
			{
				newLocation = sf::Vector2f(j - 1, i);
				m_tiles[location].addEdge(newLocation, m_tiles[newLocation]);
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
			for (auto &t : m_tiles)
			{
				if (t.second.getRect().intersects(sf::FloatRect(location.x * m_tileSize, location.y * m_tileSize, 2, 2)))
				{
					location = t.first;
					tileFound = true;
					targetTile = &t.second;
				}
			}
			if (tileFound)
			{
				Forest f = Forest(location, m_resourceManager->getTexture("tileset"), m_resourceManager->getTexture("highlightBorder"), m_resourceManager->getTexture("enemyBorder"), m_tileSize);
				for (auto pair : targetTile->getAdj())
				{
					auto &p = pair.first;
					auto &e = pair.second;
					f.addEdge(p, *e);
				}
				f.setRect(sf::FloatRect(location.x * m_tileSize, location.y * m_tileSize, m_tileSize, m_tileSize));
				m_tiles[location] = f;
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
			for (auto &t : m_tiles)
			{
				if (t.second.getRect().intersects(sf::FloatRect(location.x * m_tileSize, location.y * m_tileSize, 2, 2)))
				{
					location = t.first;
					tileFound = true;
					targetTile = &t.second;
				}
			}
			if (tileFound)
			{
				Sea s = Sea(location, m_resourceManager->getTexture("tileset"), m_resourceManager->getTexture("highlightBorder"), m_resourceManager->getTexture("enemyBorder"), m_tileSize);
				for (auto pair : targetTile->getAdj())
				{
					auto &p = pair.first;
					auto &e = pair.second;
					s.addEdge(p, *e);
				}
				s.setRect(sf::FloatRect(location.x * m_tileSize, location.y * m_tileSize, m_tileSize, m_tileSize));
				s.setUnit(m_tiles[location].getUnit());
				m_tiles[location] = s;
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
			m_tiles[location].setUnit(new Tank(location, playerNo, m_resourceManager->getTexture("spritesheet"), m_tileSize));
			m_units.push_back(m_tiles[location].getUnit());
			tankNo++;
		}
		int bomberNo = 0;
		while (!file["Units"][u]["Bomber"][bomberNo].is_null())
		{
			auto position = file["Units"][u]["Bomber"][bomberNo]["Position"];
			auto playerNo = file["Units"][u]["Bomber"][bomberNo]["Player"].get<int>();
			location = sf::Vector2f(position[0], position[1]);
			m_tiles[location].setUnit(new Bomber(location, playerNo, m_resourceManager->getTexture("spritesheet"), m_tileSize));
			m_units.push_back(m_tiles[location].getUnit());
			bomberNo++;
		}
		int heliNo = 0;
		while (!file["Units"][u]["Heli"][heliNo].is_null())
		{
			auto position = file["Units"][u]["Heli"][heliNo]["Position"];
			auto playerNo = file["Units"][u]["Heli"][heliNo]["Player"].get<int>();
			location = sf::Vector2f(position[0], position[1]);
			m_tiles[location].setUnit(new Heli(location, playerNo, m_resourceManager->getTexture("spritesheet"), m_tileSize));
			m_units.push_back(m_tiles[location].getUnit());
			heliNo++;
		}
		int aaNo = 0;
		while (!file["Units"][u]["AntiAir"][aaNo].is_null())
		{
			auto position = file["Units"][u]["AntiAir"][aaNo]["Position"];
			auto playerNo = file["Units"][u]["AntiAir"][aaNo]["Player"].get<int>();
			location = sf::Vector2f(position[0], position[1]);
			m_tiles[location].setUnit(new AntiAir(location, playerNo, m_resourceManager->getTexture("spritesheet"), m_tileSize));
			m_units.push_back(m_tiles[location].getUnit());
			aaNo++;
		}
		u++;
	}
}

void Map::update(float dt)
{
	for (auto &t : m_tiles)
	{
		if (t.second.getUnit())
		{
			t.second.getUnit()->animatePath(dt);
		}
	}
}

void Map::render(sf::RenderWindow & window, float tileSize)
{
	for (auto &t : m_tiles)
	{
		t.second.render(window);
	}
	for (auto u : m_units)
	{
		u->render(window);
	}
	//for (auto &t :m_tiles)
	//{
	//	if (t.second.getUnit())
	//	{
	//		t.second.getUnit()->render(window);
	//	}
	//}
	window.draw(m_visualBorder);
}

void Map::leftclickMap(sf::Vector2f v)
{
	sf::Vector2f mousePosition = sf::Vector2f(floor(v.x / m_tileSize), floor(v.y / m_tileSize));
	sf::Vector2f tileLocation;
	Tile* targetTile = nullptr;
	for (auto &t : m_tiles)
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
			//Checks if there is no actively selected unit
			if (selectedUnit == nullptr)
			{
				if (targetTile->getUnit()->getTurn())
				{
					if (targetTile->getUnit()->getOwner() == *m_playerTurn)
					{
						startTile = *targetTile;
						selectedUnit = targetTile->getUnit();
						moveSearch(m_tiles[tileLocation], m_tiles[tileLocation].getUnit()->getRemainingMoves());
						std::cout << "Clicked: " << tileLocation.x << ", " << tileLocation.y << std::endl;
					}
				}
			}
			//Checks if the targeted unit is an enemy and is within range of the selected unit
			else if (m_tiles[tileLocation].getUnit()->getOwner() != selectedUnit->getOwner() && checkRange(m_tiles[tileLocation]))
			{
				Unit* targetUnit = m_tiles[tileLocation].getUnit();
				Tile* closest = getClosest(m_tiles[tileLocation]);
				//Damage the units
				targetUnit->damage(selectedUnit->getDamageChartValue(targetUnit->getType()) + 10 - targetTile->getDefense());
				if (targetUnit->getHealth() <= 0)
				{
					m_tiles[targetUnit->getLocation()].setUnit(nullptr);
					m_units.erase(std::remove(m_units.begin(), m_units.end(), targetUnit), m_units.end());
					targetUnit = nullptr;
				}
				if (targetUnit)
				{
					selectedUnit->damage(targetUnit->getDamageChartValue(selectedUnit->getType()) - closest->getDefense());
					if (selectedUnit->getHealth() <= 0)
					{
						m_tiles[selectedUnit->getLocation()].setUnit(nullptr);
						m_units.erase(std::remove(m_units.begin(), m_units.end(), selectedUnit), m_units.end());
						selectedUnit = nullptr;
					}
				}
				if (selectedUnit)
				{
					if (&m_tiles[selectedUnit->getLocation()] != closest)
					{
						bool isStart = false;
						std::list<sf::Vector2f> output;
						Tile previous = *closest;
						while (!isStart)
						{
							if (!(startTile == previous))
							{
								output.push_back(previous.getLocation());
								previous = *previous.getPrevious();
							}
							else
							{
								isStart = true;
							}
						}
						selectedUnit->setPath(output);

						closest->setUnit(selectedUnit);
						m_tiles[selectedUnit->getLocation()].setUnit(nullptr);
					}
					m_tiles[m_targetLocation].getUnit()->moveTaken(m_tiles[m_targetLocation].getSCost());
					m_tiles[m_targetLocation].getUnit()->setTurn(false);
				}
				selectedUnit = nullptr;
				clearTiles();
			}
		}
		else if (m_tiles[tileLocation].getHighlighted() == true)
		{
			bool isStart = false;
			std::list<sf::Vector2f> output;
			Tile previous = m_tiles[tileLocation];
			while (!isStart)
			{
				if (!(startTile == previous))
				{
					output.push_back(previous.getLocation());
					previous = *previous.getPrevious();
				}
				else
				{
					isStart = true;
				}
			}
			selectedUnit->setPath(output);
			m_tiles[tileLocation].setUnit(selectedUnit);
			m_tiles[selectedUnit->getLocation()].setUnit(nullptr);
			selectedUnit = nullptr;
			m_tiles[tileLocation].getUnit()->moveTaken(m_tiles[tileLocation].getSCost());
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
	for (auto &tile : m_tiles)
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
			int movesRemaining = queue.front()->getSCost() - start.getUnit()->getMoveChartCost(e->getType());
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
						if (start.getUnit()->getDamageChartValue(e->getUnit()->getType()) > 0)
						{
							e->setEnemy(true);
						}
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
						if (start.getUnit()->getDamageChartValue(e->getUnit()->getType()) > 0)
						{
							e->setEnemy(true);
						}
					}
				}
			}
		}
		queue.pop_front();
	}
}

void Map::clearTiles()
{
	for (auto const& a : m_tiles)
	{
		m_tiles[a.first].setHighlight(false);
		m_tiles[a.first].setEnemy(false);
	}
}

void Map::turnUpkeep()
{
	for (auto const& a : m_tiles)
	{
		auto t = a.second;
		if (t.getUnit())
		{
			auto u = t.getUnit();
			if (u->getOwner() == *m_playerTurn)
			{
				u->upkeep();
			}
		}
	}
}

bool Map::checkRange(Tile & tile)
{
	for (auto& pair : tile.getAdj())
	{
		auto t = pair.second;
		if (t->getHighlighted() && !t->getUnit())
		{
			return true;
		}
	}
	return false;
}

bool Map::checkTile(sf::Vector2f v)
{
	if (&m_tiles[v] != nullptr)
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
	for (auto &t : m_tiles)
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
		Forest f = Forest(tileLocation, rm.getTexture("tileset"), rm.getTexture("highlightBorder"), rm.getTexture("enemyBorder"), m_tileSize);
		for (auto pair : targetTile->getAdj())
		{
			auto &p = pair.first;
			auto &e = pair.second;
			f.addEdge(p, *e);
		}
		f.setRect(sf::FloatRect(tileLocation.x * m_tileSize, tileLocation.y * m_tileSize, m_tileSize, m_tileSize));
		f.setUnit(m_tiles[tileLocation].getUnit());
		m_tiles[tileLocation] = f;
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
			if (a->getUnit() == selectedUnit)
			{
				highest = a;
				m_targetLocation = pair.first;
				break;
			}
			else
			{
				if (!a->getUnit())
				{
					if (highest)
					{
						if (highest->getSCost() < a->getSCost())
						{
							highest = a;
							m_targetLocation = pair.first;
							cost = highest->getSCost();
						}
					}
					else
					{
						highest = a;
						m_targetLocation = pair.first;
						cost = highest->getSCost();
					}
				}
			}
		}
	}
	return highest;
}

sf::Vector2f Map::convertToKey(sf::Vector2f v)
{
	return sf::Vector2f(floor(v.x / m_tileSize), floor(v.y / m_tileSize));
}

Tile & Map::getTile(sf::Vector2f v)
{
	return m_tiles[v];
}

Unit & Map::getUnit(sf::Vector2f v)
{
	return *m_tiles[v].getUnit();
}
