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

Map::Map(int x, int y)
{
	sizeX = x;
	sizeY = y;
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
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			Plains p = Plains();
			tiles[sf::Vector2f(j,i)] = p;
			sf::Vector2f location = sf::Vector2f(j, i);
			sf::Vector2f newLocation;
			int current = (j + (i * 50));
			if (i > 0)
			{
				newLocation = sf::Vector2f(j, i - 1);
				tiles[location].addEdge(tiles[newLocation]);
			}
			if (j + 1 < 50)
			{
				newLocation = sf::Vector2f(j + 1, i);
				tiles[location].addEdge(tiles[newLocation]);
			}
			if (i + 1 < 50)
			{
				newLocation = sf::Vector2f(j, i + 1);
				tiles[location].addEdge(tiles[newLocation]);
			}
			if (j > 0)
			{
				newLocation = sf::Vector2f(j - 1, i);
				tiles[location].addEdge(tiles[newLocation]);
			}
		}
	}
	sf::Vector2f location = sf::Vector2f(10, 6);
	tiles[location].setUnit(new Tank(location));
}

void Map::render(sf::RenderWindow & window)
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
		tileTexture.setPosition(t.first.x * 64, t.first.y * 64);
		tileTexture.setSize(sf::Vector2f(64, 64));
		sf::RectangleShape highlight;
		if (t.second.getHighlighted() == true)
		{
			highlight.setTexture(&highlightBorder);
			highlight.setPosition(t.first.x * 64, t.first.y * 64);
			highlight.setSize(sf::Vector2f(64, 64));
			//highlight.setFillColor(sf::Color(18, 209, 226, 120));
		}
		else
		{
			tileTexture.setOutlineThickness(0);
		}
		std::string unitType;
		if (t.second.getUnit() != nullptr)
		{
			unitType = t.second.getUnit()->getType();
		}
		sf::RectangleShape unitTexture;
		unitTexture.setTexture(&spritesheet);
		if (unitType == "Tank")
		{
			unitTexture.setTextureRect(sf::IntRect(48, 2, 24, 24));
			unitTexture.setFillColor(sf::Color(100, 100, 255));
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
		unitTexture.setPosition((unitLocation.x) * 64, (unitLocation.y) * 64);
		unitTexture.setSize(sf::Vector2f(64, 64));
		window.draw(tileTexture);
		window.draw(highlight);
		window.draw(unitTexture);
		
	}
}

void Map::leftclick(sf::Event e)
{
	sf::Vector2f mousePosition = sf::Vector2f(ceil(e.mouseButton.x / 64), ceil(e.mouseButton.y / 64));
	sf::Vector2f tileLocation = sf::Vector2f(mousePosition.x, mousePosition.y);
	if (tiles[tileLocation].getUnit())
	{
		selectedUnit = tiles[tileLocation].getUnit();
		moveSearch(tiles[tileLocation], tiles[tileLocation].getUnit()->getMoves());
		//expandtile(sf::Vector2f(static_cast<int>((mousePosition.x) + 1), static_cast<int>((mousePosition.y) + 1)), units[tileLocation].getMoves());
		std::cout << "Clicked: " << tileLocation.x << ", " << tileLocation.y << std::endl;
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
	//start.setHighlight(true);
	queue.push_back(&start);

	int cost = 1;
	while (!queue.empty())
	{
		int originCost = queue.front()->getCost();

		for (auto &e : queue.front()->getAdj())
		{
			int movesRemaining = queue.front()->getSCost() - e->getCost();
			if (movesRemaining >= 0)
			{
				if (movesRemaining > e->getSCost())
				{
					e->setVisited(false);
				}
				if (e->getVisited() == false)
				{
					e->setSCost(movesRemaining);
					e->setVisited(true);
					e->setHighlight(true);
					queue.push_back(e);
				}
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
	}
}

void Map::fButton(sf::Vector2i v)
{
	sf::Vector2f mousePosition = sf::Vector2f(ceil(v.x / 64), ceil(v.y / 64));
	sf::Vector2f tileLocation = sf::Vector2f(mousePosition.x, mousePosition.y);
	Forest f = Forest();
	for (auto &e : tiles[tileLocation].getAdj())
	{
		f.addEdge(*e);
	}
	f.setUnit(tiles[tileLocation].getUnit());
	tiles[tileLocation] = f;
}