#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "BaseMoveChart.h"
class Unit
{
public:
	Unit() {};
	Unit(sf::Vector2f location) {};
	~Unit() {};
	virtual void setLocation(sf::Vector2f location) { this->m_gridLocation = location; }
	virtual void moveTaken(int movement) { this->m_remainingMoves = movement; }
	virtual void upkeep() { this->m_remainingMoves = this->m_movement; this->m_turnTaken = true; }
	virtual sf::Vector2f getLocation() { return this->m_gridLocation; }
	virtual std::string getType() {	return this->type; }
	virtual int getMoves() { return this->m_movement;	}
	virtual int getRemainingMoves() { return this->m_remainingMoves; }
	virtual int getHealth()	{ return this->m_health; }
	virtual int getPower() { return this->m_power; }
	virtual int getOwner() { return this->m_player; }
	virtual int getChartCost(TileTypes t) { return this->m_chart.getCost(t); }
	virtual bool getTurn() { return this->m_turnTaken; }
	virtual void setTurn(bool b) { this->m_turnTaken = b; }
	virtual void damage(int d) { m_health -= d; }

	virtual void render(sf::RenderWindow& window) {
		m_sprite.setPosition((m_gridLocation.x) * m_tileSize, (m_gridLocation.y) * m_tileSize);
		window.draw(m_sprite);
	}
protected:
	int m_health, m_maxHealth, m_tileSize, m_power, m_movement, m_remainingMoves, m_player;
	bool m_turnTaken = true;
	std::string type;
	BaseMoveChart m_chart;
	sf::Vector2f m_gridLocation;
	sf::RectangleShape m_sprite;
};