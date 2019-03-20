#pragma once
#include <map>
#include <list>
#include <optional>
#include "SFML/Graphics.hpp"
#include "BattlePreview.h"
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
	std::list<BattlePreview> getBattles(sf::Vector2f v) { return m_battles[v]; }
	void addBattle(sf::Vector2f v, BattlePreview b) { m_battles[v].push_back(b); }
	void clearBlackboard() { m_battles.clear(); }
private:
	//std::map<std::pair<sf::Vector2f, sf::Vector2f>, std::optional<std::pair<int, int>>> damagePreview;
	std::map<sf::Vector2f, std::list<BattlePreview>, VectorComparator> m_battles;
};