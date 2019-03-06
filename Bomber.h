#pragma once
#include "Unit.h"
#include "AirMoveChart.h"

class Bomber : public Unit
{
public:
	Bomber()
	{
		m_maxHealth = 100;
		m_health = m_maxHealth;
		m_power = 80;
		m_movement = 7;
		type = "Bomber";
		m_gridLocation = sf::Vector2f(1, 1);
	};
	Bomber(sf::Vector2f location, int p, sf::Texture& tileset, int tSize)
	{
		m_maxHealth = 100;
		m_health = m_maxHealth;
		m_power = 50;
		m_movement = 7;
		type = "Bomber";
		m_gridLocation = location;
		m_player = p;
		m_tileSize = tSize;
		m_sprite.setTexture(&tileset);
		m_sprite.setTextureRect(sf::IntRect(24, 232, 24, 24));
		if (m_player == 1)
		{
			m_sprite.setFillColor(sf::Color(100, 100, 255));
		}
		else if (m_player == 2)
		{
			m_sprite.setFillColor(sf::Color(255, 100, 100));
		}
		m_sprite.setSize(sf::Vector2f(m_tileSize, m_tileSize));
		m_chart = AirMoveChart();
	};
};