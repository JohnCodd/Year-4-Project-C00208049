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
	virtual int getMoves()
	{
		return this->movement;
	}
	virtual int getOwner()
	{
		return this->player;
	}
	virtual bool getTurn()
	{
		return this->turnTaken;
	}
	virtual void setTurn(bool b)
	{
		this->turnTaken = b;
	}
protected:
	int health;
	int power;
	int movement;
	int player;
	bool turnTaken;
	std::string type;
	sf::Vector2f gridLocation;
};