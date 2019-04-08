#include "UnitAgent.h"



UnitAgent::UnitAgent(Blackboard& b, sf::Vector2f v): m_blackboard(b), m_position(v)
{
}


UnitAgent::~UnitAgent()
{
}

void UnitAgent::execute()
{
	std::vector<BattlePreview> data;
	std::vector<Unit>& m_enemies = m_blackboard.getEnemies();
	if (m_enemies.size() > 0)
	{
		sf::Vector2f targetPos;
		int u = rand() % m_enemies.size();
		targetPos = m_enemies.at(u).getLocation();
		data = m_blackboard.getBattles(targetPos);
		if (data.size() == 0)
		{
			BattlePreview battle;
			battle.setAttackerPos(m_position);
			battle.setDefenderPos(targetPos);
			m_blackboard.addBattle(targetPos, battle);
			m_enemies.erase(m_enemies.begin() + u);
		}
	}
}