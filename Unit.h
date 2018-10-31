#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Unit
{
public:
	Unit() {};
	Unit(sf::Vector2f location) {};
	~Unit() {};
	virtual void setLocation(sf::Vector2f location) {
		this->gridLocation = location;
	}
	virtual sf::Vector2f getLocation()
	{
		return this->gridLocation;
	}
	virtual std::string getType()
	{
		return this->type;
	}
protected:
	int health;
	int power;
	int movement;
	std::string type;
	sf::Vector2f gridLocation;
};