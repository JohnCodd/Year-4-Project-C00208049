#pragma once
#include "Tile.h"
class Forest : public Tile
{
public:
	Forest(sf::Vector2f location, sf::Texture& tileset, sf::Texture& hBlue, sf::Texture& hRed, int tSize)
		: Tile(location, tileset, hRed, hBlue, tSize)
	{
		moveCost = 3;
		defense = 10;
		type = "Forest";
		sprite.setTextureRect(sf::IntRect(96, 64, 16, 16));
	};
	~Forest() {};
};