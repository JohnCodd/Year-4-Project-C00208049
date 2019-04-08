#pragma once
#include "SFML/Graphics.hpp"
class BattlePreview
{
public:
	BattlePreview();
	~BattlePreview();
	sf::Vector2f getAttackerPos() { return m_attackerPos; }
	sf::Vector2f getDefenderPos() { return m_defenderPos; }
	int getAttackerDamage() { return m_attackerDamage; }
	int getDefenderDamage() { return m_defenderDamage; }
	void setAttackerPos(sf::Vector2f v) { m_attackerPos = v; }
	void setDefenderPos(sf::Vector2f v) { m_defenderPos = v; }
	void setAttackerDamage(int d) { m_attackerDamage = d; }
	void setDefenderDamage(int d) { m_defenderDamage = d; }
private:
	sf::Vector2f m_attackerPos, m_defenderPos;
	int m_attackerDamage, m_defenderDamage;
};

