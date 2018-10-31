#pragma once
#include "Unit.h"

class Tank : public Unit
{
public:
	Tank()
	{
		health = 100;
		power = 50;
		movement = 6;
		type = "Tank";
		gridLocation = sf::Vector2f(1, 1);
	};
	Tank(sf::Vector2f location)
	{
		health = 100;
		power = 50;
		movement = 6;
		type = "Tank";
		gridLocation = location;
	};
	~Tank() {};
};