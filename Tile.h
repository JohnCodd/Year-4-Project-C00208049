#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Tile
{
public:
	Tile() {};
	~Tile() {};
protected:
	int moveCost;
	float defense;
	std::string type;
	sf::Texture* m_texture;
};