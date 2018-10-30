#include "Map.h"

Map::Map()
{
	sizeX = 10;
	sizeY = 10;
	for (int i = 1; i < sizeY; i++)
	{
		for (int j = 1; j < sizeX; j++)
		{
			Plains p = Plains();
			tiles[j + "," + i] = p;
		}
	}
}

Map::Map(int x, int y)
{
	sizeX = x;
	sizeY = y;
	for (int i = 1; i < sizeY; i++)
	{
		for (int j = 1; j < sizeX; j++)
		{
			Plains p = Plains();
			tiles[j + "," + i] = p;
		}
	}
}

void Map::render(sf::RenderWindow & window)
{
	for (int i = 1; i < sizeY; i++)
	{
		for (int j = 1; j < sizeX; j++)
		{
			sf::RectangleShape square;
			square.setPosition(j * 10, i * 10);
			square.setSize(sf::Vector2f(10, 10));
			square.setFillColor(sf::Color(0, 255, 0));
			window.draw(square);
		}
	}
}