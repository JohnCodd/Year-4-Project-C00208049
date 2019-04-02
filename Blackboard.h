#pragma once
#include <map>
#include <list>
#include <optional>
#include "SFML/Graphics.hpp"
#include "BattlePreview.h"
#include "Unit.h"
class Blackboard
{
	struct VectorComparator
	{
		bool operator() (sf::Vector2f lhs, sf::Vector2f rhs) const
		{
			return std::tie(lhs.x, rhs.y) < std::tie(rhs.x, lhs.y);
		}
	};
public:
	Blackboard();
	~Blackboard();
	//std::map<std::pair<sf::Vector2f, sf::Vector2f>, std::optional<std::pair<int, int>>> getPreview();
	//void setPreviewDamage(std::pair<sf::Vector2f, sf::Vector2f> pos, std::pair<int, int> damage);
	std::vector<BattlePreview> getBattles(sf::Vector2f v) { return m_battles[v]; }
	std::vector<Unit>& getEnemies() { return m_enemies; }
	void addBattle(sf::Vector2f v, BattlePreview b) { m_battles[v].push_back(b); }
	void setEnemies(std::vector<Unit> e) { m_enemies = e; }
	void clearBlackboard() { m_battles.clear(); m_enemies.clear(); }
private:
	//std::map<std::pair<sf::Vector2f, sf::Vector2f>, std::optional<std::pair<int, int>>> damagePreview;
	std::map<sf::Vector2f, std::vector<BattlePreview>, VectorComparator> m_battles;
	std::vector<Unit> m_enemies;
};