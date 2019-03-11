#pragma once
#include "Unit.h"
#include "AntiAirMoveChart.h"
#include "AntiAirDamageChart.h"

class AntiAir : public Unit
{
public:
	AntiAir()
	{
		m_maxHealth = 100;
		m_health = m_maxHealth;
		m_movement = 5;
		m_remainingMoves = m_movement;
		m_type = UnitTypes::AntiAir;
		m_gridLocation = sf::Vector2f(1, 1);
	};
	AntiAir(sf::Vector2f location, int p, sf::Texture& tileset, int tSize)
	{
		m_maxHealth = 100;
		m_health = m_maxHealth;
		m_movement = 5;
		m_remainingMoves = m_movement;
		m_type = UnitTypes::AntiAir;
		m_gridLocation = location;
		m_player = p;
		m_tileSize = tSize;
		m_sprite.setTexture(&tileset);
		m_sprite.setTextureRect(sf::IntRect(193, 106, 22, 22));
		if (m_player == 1)
		{
			m_sprite.setFillColor(sf::Color(100, 100, 255));
		}
		else if (m_player == 2)
		{
			m_sprite.setFillColor(sf::Color(255, 100, 100));
		}
		m_sprite.setSize(sf::Vector2f(m_tileSize, m_tileSize));
		m_moveChart = AntiAirMoveChart();
		m_damageChart = AntiAirDamageChart();
	}
};