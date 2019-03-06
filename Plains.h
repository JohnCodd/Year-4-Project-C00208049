#pragma once
#include "Tile.h"
class Plains : public Tile
{
public:
	Plains(sf::Vector2f location, sf::Texture& tileset, sf::Texture& hBlue, sf::Texture& hRed, int tSize)
		: Tile(location, tileset, hRed, hBlue, tSize)
	{
		m_moveCost = 1;
		m_defense = 0;
		m_type = TileTypes::Plains;
		m_sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
	};
	~Plains() {};
};