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
	for (int i = 1; i < sizeY; i++)
	{
		for (int j = 1; j < sizeX; j++)
		{
			Plains p = Plains();
			p.highlight();
			//sf::RectangleShape texture;
			//texture.setTexture(&tileset);
			//texture.setSize(sf::Vector2f(16, 16));
			//texture.setTextureRect(sf::IntRect(16, 16, 16, 16));
			//p.setTexture(&texture);
			tiles[j + "," + i] = p;
			Tank t = Tank(sf::Vector2f(10, 10));
			units["10,10"] = t;
		}
	}
}

void Map::render(sf::RenderWindow & window)
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			sf::RectangleShape square;
			square.setPosition(j * 64, i * 64);
			square.setSize(sf::Vector2f(64, 64));
			square.setFillColor(sf::Color(0, 255, 0));
			window.draw(square);
			sf::String tileType = tiles[(j + 1) + "," + (i + 1)].getType();
			sf::RectangleShape tileTexture;
			tileTexture.setTexture(&tileset);
			if (tileType == "Plains")
			{
				tileTexture.setTextureRect(sf::IntRect(16, 0, 16, 16));
			}
			tileTexture.setPosition(j * 64, i * 64);
			tileTexture.setSize(sf::Vector2f(64, 64));
			sf::RectangleShape highlight;
			if (tiles[(j + 1) + "," + (i + 1)].getHighlighted() == true)
			{
				highlight.setPosition(j * 64, i * 64);
				highlight.setSize(sf::Vector2f(64, 64));
				highlight.setFillColor(sf::Color(18, 209, 226, 120));
				highlight.setOutlineColor(sf::Color::Red);
				highlight.setOutlineThickness(2);
			}
			sf::String unitType = units[(j + 1) + "," + (i + 1)].getType();
			sf::RectangleShape unitTexture;
			unitTexture.setTexture(&spritesheet);
			if (unitType == "Tank")
			{
				unitTexture.setTextureRect(sf::IntRect(48, 2, 24, 24));
			}
			else
			{
				unitTexture.setFillColor(sf::Color::Transparent);
			}
			sf::Vector2f unitLocation = units[(j + 1) + "," + (i + 1)].getLocation();
			unitTexture.setPosition((unitLocation.x - 1) * 64, (unitLocation.y - 1) * 64);
			unitTexture.setSize(sf::Vector2f(64, 64));
			window.draw(tileTexture);
			window.draw(highlight);
			window.draw(unitTexture);
		}
	}
}