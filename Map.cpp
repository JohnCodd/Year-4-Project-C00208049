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
			Tank t = Tank(sf::Vector2f(5, 5));
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
			std::string tileType = tiles[std::to_string(j + 1) + "," + std::to_string(i + 1)].getType();
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
			if (tiles[std::to_string(j + 1) + "," + std::to_string(i + 1)].getHighlighted() == true)
			{
				highlight.setPosition(j * 64, i * 64);
				highlight.setSize(sf::Vector2f(64, 64));
				highlight.setFillColor(sf::Color(18, 209, 226, 120));
				//std::cout << "Highlighting: " << highlight.getPosition().x << "," << highlight.getPosition().y << std::endl;
				/*highlight.setOutlineColor(sf::Color::Red);
				highlight.setOutlineThickness(2);*/
			}
			sf::String unitType = units[std::to_string(j + 1) + "," + std::to_string(i + 1)].getType();
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
			sf::Vector2f unitLocation = units[std::to_string(j + 1) + "," + std::to_string(i + 1)].getLocation();
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
	tiles[tileLocation].highlight();
	std::cout << "Clicked: " << tileLocation << std::endl;
}