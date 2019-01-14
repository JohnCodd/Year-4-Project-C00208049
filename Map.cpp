#include "Map.h"

Map::Map()
{
	sizeX = 10;
	sizeY = 10;
	if (!tileset.loadFromFile("./Resources/Tilesets/tileset.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	for (int i = 1; i < sizeY; i++)
	{
		for (int j = 1; j < sizeX; j++)
		{
			Plains p = Plains();
			//sf::RectangleShape texture;
			//texture.setTexture(&tileset);
			//texture.setSize(sf::Vector2f(16, 16));
			//texture.setTextureRect(sf::IntRect(16, 16, 16, 16));
			//p.setTexture(&texture);
			tiles[sf::Vector2f(j,i)] = p;
		}
	}
}

Map::Map(int x, int y, int tSize, int& turn)
{
	sizeX = x;
	sizeY = y;
	tileSize = tSize;
	playerTurn = &turn;
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
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			Plains p = Plains();
			p.setRect(sf::FloatRect(j * tileSize, i * tileSize, tileSize, tileSize));
			tiles[sf::Vector2f(j,i)] = p;
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
	tiles[location].setUnit(new Tank(location, 1));
	location = sf::Vector2f(6, 10);
	tiles[location].setUnit(new Tank(location, 2));
	location = sf::Vector2f(4, 10);
	tiles[location].setUnit(new Tank(location, 1));
}

void Map::render(sf::RenderWindow & window, float tileSize)
{
	for (auto &t : tiles)
	{
		std::string tileType = t.second.getType();
		sf::RectangleShape tileTexture;
		tileTexture.setTexture(&tileset);
		if (tileType == "Plains")
		{
			tileTexture.setTextureRect(sf::IntRect(16, 0, 16, 16));
		}
		else if (tileType == "Forest")
		{
			tileTexture.setTextureRect(sf::IntRect(96, 64, 16, 16));
		}
		else
		{
			tileTexture.setFillColor(sf::Color::Transparent);
		}
		tileTexture.setPosition(t.first.x * tileSize, t.first.y * tileSize);
		tileTexture.setSize(sf::Vector2f(tileSize, tileSize));
		sf::RectangleShape highlight;
		if (t.second.getHighlighted() == true)
		{
			highlight.setTexture(&highlightBorder);
			highlight.setPosition(t.first.x * tileSize, t.first.y * tileSize);
			highlight.setSize(sf::Vector2f(tileSize, tileSize));
			//highlight.setFillColor(sf::Color(18, 209, 226, 120));
		}
		else if (t.second.getEnemy() == true)
		{
			highlight.setTexture(&enemyBorder);
			highlight.setPosition(t.first.x * tileSize, t.first.y * tileSize);
			highlight.setSize(sf::Vector2f(tileSize, tileSize));
		}
		else
		{
			tileTexture.setOutlineThickness(0);
		}
		std::string unitType;
		sf::RectangleShape unitTexture;
		int player;
		if (t.second.getUnit() != nullptr)
		{
			unitType = t.second.getUnit()->getType();
			player = t.second.getUnit()->getOwner();
			if (player == 1)
			{
				unitTexture.setFillColor(sf::Color(100, 100, 255));
			}
			else if (player == 2)
			{
				unitTexture.setFillColor(sf::Color(255, 100, 100));
			}
		}
		unitTexture.setTexture(&spritesheet);
		if (unitType == "Tank")
		{
			unitTexture.setTextureRect(sf::IntRect(48, 2, 24, 24));
		}
		else
		{
			unitTexture.setFillColor(sf::Color::Transparent);
		}
		sf::Vector2f unitLocation;
		if (t.second.getUnit())
		{
			unitLocation = t.second.getUnit()->getLocation();
		}
		unitTexture.setPosition((unitLocation.x) * tileSize, (unitLocation.y) * tileSize);
		unitTexture.setSize(sf::Vector2f(tileSize, tileSize));
		window.draw(tileTexture);
		window.draw(highlight);
		window.draw(unitTexture);
		
	}
}

void Map::leftclickMap(sf::Vector2f v)
{
	sf::Vector2f mousePosition = sf::Vector2f(floor(v.x / tileSize), floor(v.y / tileSize));
	sf::Vector2f tileLocation;
	for (auto &t : tiles)
	{
		if (t.second.getRect().intersects(sf::FloatRect(v.x, v.y, 2, 2)))
		{
			tileLocation = t.first;
		}
	}
	if (tiles[tileLocation].getUnit())
	{
		if (selectedUnit == nullptr && tiles[tileLocation].getUnit()->getOwner() == *playerTurn)
		{
			selectedUnit = tiles[tileLocation].getUnit();
			moveSearch(tiles[tileLocation], tiles[tileLocation].getUnit()->getMoves());
			//expandtile(sf::Vector2f(static_cast<int>((mousePosition.x) + 1), static_cast<int>((mousePosition.y) + 1)), units[tileLocation].getMoves());
			std::cout << "Clicked: " << tileLocation.x << ", " << tileLocation.y << std::endl;
		}
		else if (tiles[tileLocation].getUnit()->getOwner() != selectedUnit->getOwner() && checkRange(tiles[tileLocation]))
		{
			tiles[tileLocation].setUnit(nullptr);
			Tile* closest = getClosest(tiles[tileLocation]);
			if (&tiles[selectedUnit->getLocation()] != closest)
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
			clearTiles();
		}
	}
	else if (tiles[tileLocation].getHighlighted() == true)
	{
		Unit movingUnit = *selectedUnit;
		movingUnit.setLocation(sf::Vector2f(mousePosition.x, mousePosition.y));
		tiles[tileLocation].setUnit(new Unit(movingUnit));
		tiles[selectedUnit->getLocation()].setUnit(nullptr);
		selectedUnit = nullptr;
		clearTiles();
	}
}

void Map::rightclick(sf::Event e)
{
	selectedUnit = nullptr;
	clearTiles();
}

void Map::expandtile(sf::Vector2f location, int moves)
{
	// Legacy code
	sf::Vector2f tileLocation;
	int movesremaining;
	sf::Vector2f newLocation;
	tileLocation = sf::Vector2f(location.x, location.y);
	tiles[tileLocation].setHighlight(true);
	tileLocation = sf::Vector2f(location.x - 1, location.y);
	if (tiles.count(tileLocation) == 1)
	{
		movesremaining = moves - tiles[tileLocation].getCost();
		if (movesremaining >= 0)
		{
			newLocation = sf::Vector2f(location.x - 1, location.y);
			expandtile(newLocation, movesremaining);
		}
	}
	tileLocation = sf::Vector2f(location.x + 1, location.y);
	if (tiles.count(tileLocation) == 1)
	{
		movesremaining = moves - tiles[tileLocation].getCost();
		if (movesremaining >= 0)
		{
			newLocation = sf::Vector2f(location.x + 1, location.y);
			expandtile(newLocation, movesremaining);
		}
	}
	tileLocation = sf::Vector2f(location.x, location.y - 1);
	if (tiles.count(tileLocation) == 1)
	{
		movesremaining = moves - tiles[tileLocation].getCost();
		if (movesremaining >= 0)
		{
			newLocation = sf::Vector2f(location.x, location.y - 1);
			expandtile(newLocation, movesremaining);
		}
	}
	tileLocation = sf::Vector2f(location.x, location.y + 1);
	if (tiles.count(tileLocation) == 1)
	{
		movesremaining = moves - tiles[tileLocation].getCost();
		if (movesremaining >= 0)
		{
			newLocation = sf::Vector2f(location.x, location.y + 1);
			expandtile(newLocation, movesremaining);
		}
	}
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
			int movesRemaining = queue.front()->getSCost() - e->getCost();
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

void Map::fButton(sf::Vector2f v)
{
	sf::Vector2f mousePosition = sf::Vector2f(ceil(v.x / tileSize), ceil(v.y / tileSize));
	sf::Vector2f tileLocation;
	for (auto &t : tiles)
	{
		if (t.second.getRect().intersects(sf::FloatRect(v.x, v.y, 2, 2)))
		{
			tileLocation = t.first;
		}
	}
	Forest f = Forest();
	for (auto pair : tiles[tileLocation].getAdj())
	{
		auto &e = pair.second;
		f.addEdge(tileLocation, *e);
	}
	f.setRect(sf::FloatRect(tileLocation.x * tileSize, tileLocation.y * tileSize, tileSize, tileSize));
	f.setUnit(tiles[tileLocation].getUnit());
	tiles[tileLocation] = f;
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