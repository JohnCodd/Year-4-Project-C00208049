#include "UnitAgent.h"



UnitAgent::UnitAgent(Blackboard& b, sf::Vector2f v, std::list<Unit>& u): m_blackboard(b), m_position(v), m_enemies(u)
{
}


UnitAgent::~UnitAgent()
{
}

void UnitAgent::execute()
{
	std::list<BattlePreview> data;
	sf::Vector2f targetPos;
	for (auto u : m_enemies)
	{
		targetPos = u.getLocation();
		data = m_blackboard.getBattles(targetPos);
		if (data.size() == 0)
		{
			BattlePreview battle;
			battle.setAttackerPos(m_position);
			battle.setDefenderPos(targetPos);
			m_blackboard.addBattle(targetPos, battle);
			break;
		}
	}
}