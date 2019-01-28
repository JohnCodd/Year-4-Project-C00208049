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
	Tank(sf::Vector2f location, int p)
	{
		maxHealth = 100;
		health = maxHealth;
		power = 50;
		movement = 6;
		type = "Tank";
		gridLocation = location;
		player = p;
	};
	~Tank() {};
};