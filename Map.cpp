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
			p.setType("Plains");
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
	for (int i = 1; i < sizeY; i++)
	{
		for (int j = 1; j < sizeX; j++)
		{
			Plains p = Plains();
			p.setType("Plains");
			//sf::RectangleShape texture;
			//texture.setTexture(&tileset);
			//texture.setSize(sf::Vector2f(16, 16));
			//texture.setTextureRect(sf::IntRect(16, 16, 16, 16));
			//p.setTexture(&texture);
			tiles[j + "," + i] = p;
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
			sf::RectangleShape texture;
			texture.setTexture(&tileset);
			if (tileType == "Plains")
			{
				texture.setTextureRect(sf::IntRect(16, 0, 16, 16));
			}
			texture.setPosition(j * 64, i * 64);
			texture.setSize(sf::Vector2f(64, 64));
			window.draw(texture);
		}
	}
}