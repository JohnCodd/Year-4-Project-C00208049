#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Unit
{
public:
	Unit() {};
	Unit(sf::Vector2f location) {};
	~Unit() {};
	virtual void setLocation(sf::Vector2f location) { this->gridLocation = location; }
	virtual sf::Vector2f getLocation() { return this->gridLocation; }
	virtual std::string getType() {	return this->type; }
	virtual int getMoves() { return this->movement;	}
	virtual int getHealth()	{ return this->health; }
	virtual int getPower() { return this->power; }
	virtual int getOwner() { return this->player; }
	virtual bool getTurn() { return this->turnTaken; }
	virtual void setTurn(bool b) { this->turnTaken = b; }
	virtual void damage(int d) { health -= d; }

	virtual void render(sf::RenderWindow& window) {
		sprite.setPosition((gridLocation.x) * tileSize, (gridLocation.y) * tileSize);
		window.draw(sprite);
	}
protected:
	int health, maxHealth, tileSize;
	int power;
	int movement;
	int player;
	bool turnTaken;
	std::string type;
	sf::Vector2f gridLocation;
	sf::RectangleShape sprite;
};