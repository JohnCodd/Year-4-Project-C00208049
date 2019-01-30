#pragma once
#include "Unit.h"

class Tank : public Unit
{
public:
	Tank()
	{
		maxHealth = 100;
		health = maxHealth;
		power = 50;
		movement = 6;
		type = "Tank";
		gridLocation = sf::Vector2f(1, 1);
	};
	Tank(sf::Vector2f location, int p, sf::Texture& tileset, int tSize)
	{
		maxHealth = 100;
		health = maxHealth;
		power = 50;
		movement = 6;
		type = "Tank";
		gridLocation = location;
		player = p;
		tileSize = tSize;
		sprite.setTexture(&tileset);
		sprite.setTextureRect(sf::IntRect(48, 2, 24, 24));
		if (player == 1)
		{
			sprite.setFillColor(sf::Color(100, 100, 255));
		}
		else if (player == 2)
		{
			sprite.setFillColor(sf::Color(255, 100, 100));
		}
		sprite.setSize(sf::Vector2f(tileSize, tileSize));
	};
	~Tank() {};
};