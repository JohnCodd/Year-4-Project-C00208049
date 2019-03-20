#include "UnitAgent.h"



UnitAgent::UnitAgent(Blackboard& b, sf::Vector2f v): m_blackboard(b), m_position(v)
{
}


UnitAgent::~UnitAgent()
{
}

void UnitAgent::execute()
{
	std::list<BattlePreview> data;
	sf::Vector2f targetPos;
	targetPos = sf::Vector2f(5, 5);
	data = m_blackboard.getBattles(targetPos);
	BattlePreview battle;
	battle.setAttackerPos(m_position);
	if (data.size() == 0)
	{
		m_blackboard.addBattle(targetPos, battle);
	}
	else
	{
		targetPos = sf::Vector2f(6, 6);
		m_blackboard.addBattle(targetPos, battle);
	}
}