#pragma once
#include "Tile.h"
class Sea : public Tile
{
public:
	Sea(sf::Vector2f location, sf::Texture& tileset, sf::Texture& hBlue, sf::Texture& hRed, int tSize)
		: Tile(location, tileset, hRed, hBlue, tSize)
	{
		m_moveCost = 1;
		m_defense = 0;
		m_type = TileTypes::Sea;
		m_sprite.setTextureRect(sf::IntRect(160, 16, 16, 16));
	};
	~Sea() {};
};