#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "BaseMoveChart.h"
#include "BaseDamageChart.h"
class Unit
{
public:
	Unit() {};
	Unit(sf::Vector2f location) {};
	~Unit() {};
	virtual void setLocation(sf::Vector2f location) { this->m_gridLocation = location; }
	virtual void moveTaken(int movement) { this->m_remainingMoves = movement; }
	virtual void upkeep() { this->m_remainingMoves = this->m_movement; this->m_turn = true; }
	virtual sf::Vector2f getLocation() { return this->m_gridLocation; }
	virtual UnitTypes getType() {	return this->m_type; }
	virtual int getMoves() { return this->m_movement;	}
	virtual int getRemainingMoves() { return this->m_remainingMoves; }
	virtual int getHealth()	{ return this->m_health; }
	virtual int getPower() { return this->m_power; }
	virtual int getOwner() { return this->m_player; }
	virtual int getMoveChartCost(TileTypes t) { return this->m_moveChart.getCost(t); }
	virtual int getDamageChartValue(UnitTypes u) { return this->m_damageChart.getDamage(u); }
	virtual bool getTurn() { return this->m_turn; }
	virtual void setTurn(bool b) { this->m_turn = b; }
	virtual void setPath(std::list<sf::Vector2f> path) { this->m_path = path; this->m_animate = true; }
	virtual void damage(int d) { m_health -= d; }
	virtual void animatePath(float dt) {
		if (m_animate)
		{
			if (m_path.size() > 0)
			{
				sf::Vector2f normalVector = normalise(m_path.back() - m_gridLocation);
				normalVector.x = (normalVector.x * m_speed) * dt;
				normalVector.y = (normalVector.y * m_speed) * dt;
				m_gridLocation += normalVector;
				if (distance(m_path.back()) < 0.01)
				{
					m_gridLocation = m_path.back();
					m_path.pop_back();
				}
			}
			else
			{
				m_animate = false;
			}
		}
	}

	virtual sf::Vector2f normalise(sf::Vector2f v) {
		float len = sqrtf(powf(v.x, 2) + powf(v.y, 2));
		return sf::Vector2f(v.x / len, v.y / len);
	}

	virtual float distance(sf::Vector2f & v)
	{
		sf::Vector2f diff = m_gridLocation - v;
		return sqrtf(powf(diff.x, 2) + powf(diff.y, 2));
	}

	virtual void render(sf::RenderWindow& window) {
		m_sprite.setPosition((m_gridLocation.x) * m_tileSize, (m_gridLocation.y) * m_tileSize);
		sf::Color c = m_sprite.getFillColor();
		if (m_turn)
		{
			c = sf::Color(c.r, c.g, c.b, 255);
		}
		else
		{
			c = sf::Color(c.r, c.g, c.b, 155);
		}
		m_sprite.setFillColor(c);
		window.draw(m_sprite);
	}
protected:
	int m_health, m_maxHealth, m_tileSize, m_power, m_movement, m_remainingMoves, m_player;
	float m_speed = 0.005f;
	bool m_turn = true;
	bool m_animate = false;
	UnitTypes m_type;
	BaseMoveChart m_moveChart;
	BaseDamageChart m_damageChart;
	sf::Vector2f m_gridLocation;
	sf::RectangleShape m_sprite;
	std::list<sf::Vector2f> m_path;
};