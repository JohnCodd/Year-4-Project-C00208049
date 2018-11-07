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
			tiles[j + "," + i] = p;
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
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			Plains p = Plains();
			//p.highlight();
			//sf::RectangleShape texture;
			//texture.setTexture(&tileset);
			//texture.setSize(sf::Vector2f(16, 16));
			//texture.setTextureRect(sf::IntRect(16, 16, 16, 16));
			//p.setTexture(&texture);
			tiles[std::string(std::to_string(static_cast<int>(j + 1)) + "," + std::to_string(static_cast<int>(i + 1)))] = p;
		}
	}
	Tank t = Tank(sf::Vector2f(10, 6));
	units["10,6"] = t;
}

void Map::render(sf::RenderWindow & window)
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			sf::RectangleShape square;
			std::string location = std::to_string(j + 1) + "," + std::to_string(i + 1);
			square.setPosition(j * 64, i * 64);
			square.setSize(sf::Vector2f(64, 64));
			square.setFillColor(sf::Color(0, 255, 0));
			window.draw(square);
			std::string tileType = tiles[location].getType();
			sf::RectangleShape tileTexture;
			tileTexture.setTexture(&tileset);
			if (tileType == "Plains")
			{
				tileTexture.setTextureRect(sf::IntRect(16, 0, 16, 16));
			}
			else
			{
				tileTexture.setFillColor(sf::Color::Transparent);
			}
			tileTexture.setPosition(j * 64, i * 64);
			tileTexture.setSize(sf::Vector2f(64, 64));
			sf::RectangleShape highlight;
			if (tiles[location].getHighlighted() == true)
			{
				highlight.setPosition(j * 64, i * 64);
				highlight.setSize(sf::Vector2f(64, 64));
				highlight.setFillColor(sf::Color(18, 209, 226, 120));
				//std::cout << "Highlighting: " << highlight.getPosition().x << "," << highlight.getPosition().y << std::endl;
				/*highlight.setOutlineColor(sf::Color::Red);
				highlight.setOutlineThickness(2);*/
			}
			std::string unitType;
			if (units.count(location) == 1)
			{
				unitType = units[location].getType();
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
			if (units.count(location) == 1)
			{
				unitLocation = units[location].getLocation();
			}
			unitTexture.setPosition((unitLocation.x - 1) * 64, (unitLocation.y - 1) * 64);
			unitTexture.setSize(sf::Vector2f(64, 64));
			window.draw(tileTexture);
			window.draw(highlight);
			window.draw(unitTexture);
		}
	}
}

void Map::leftclick(sf::Event e)
{
	sf::Vector2f mousePosition = sf::Vector2f(ceil(e.mouseButton.x / 64), ceil(e.mouseButton.y / 64));
	std::string tileLocation = std::to_string(static_cast<int>((mousePosition.x) + 1)) + "," + std::to_string(static_cast<int>((mousePosition.y) + 1));
	if (units.count(tileLocation) == 1)
	{
		selectedUnit = tileLocation;
		expandtile(sf::Vector2f(static_cast<int>((mousePosition.x) + 1), static_cast<int>((mousePosition.y) + 1)), units[tileLocation].getMoves());
		std::cout << "Clicked: " << tileLocation << std::endl;
	}
	else if (tiles[tileLocation].getHighlighted() == true)
	{
		units[selectedUnit].setLocation(sf::Vector2f(mousePosition.x + 1, mousePosition.y + 1));
		units[tileLocation] = units[selectedUnit];
		units.erase(selectedUnit);
		selectedUnit = "";
		clearTiles();
	}
}

void Map::rightclick(sf::Event e)
{
	selectedUnit = "";
	clearTiles();
}

void Map::expandtile(sf::Vector2f location, int moves)
{
	std::string tileLocation;
	int movesremaining;
	sf::Vector2f newLocation;
	tileLocation = std::to_string(static_cast<int>(location.x)) + "," + std::to_string(static_cast<int>(location.y));
	if (tiles[tileLocation].getHighlighted() == false)
	{
		tiles[tileLocation].highlight();
	}
	tileLocation = std::to_string(static_cast<int>(location.x - 1)) + "," + std::to_string(static_cast<int>(location.y));
	if (tiles.count(tileLocation) == 1)
	{
		movesremaining = moves - tiles[tileLocation].getCost();
		if (movesremaining >= 0)
		{
			newLocation = sf::Vector2f(location.x - 1, location.y);
			expandtile(newLocation, movesremaining);
		}
	}
	tileLocation = std::to_string(static_cast<int>(location.x + 1)) + "," + std::to_string(static_cast<int>(location.y));
	if (tiles.count(tileLocation) == 1)
	{
		movesremaining = moves - tiles[tileLocation].getCost();
		if (movesremaining >= 0)
		{
			newLocation = sf::Vector2f(location.x + 1, location.y);
			expandtile(newLocation, movesremaining);
		}
	}
	tileLocation = std::to_string(static_cast<int>(location.x)) + "," + std::to_string(static_cast<int>(location.y - 1));
	if (tiles.count(tileLocation) == 1)
	{
		movesremaining = moves - tiles[tileLocation].getCost();
		if (movesremaining >= 0)
		{
			newLocation = sf::Vector2f(location.x, location.y - 1);
			expandtile(newLocation, movesremaining);
		}
	}
	tileLocation = std::to_string(static_cast<int>(location.x)) + "," + std::to_string(static_cast<int>(location.y + 1));
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

void Map::clearTiles()
{
	for (auto const& a : tiles)
	{
		if (tiles[a.first].getHighlighted() == true)
		{
			tiles[a.first].highlight();
		}
	}
}
