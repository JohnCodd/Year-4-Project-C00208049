#pragma once
#include "Blackboard.h"
#include "Unit.h"
class UnitAgent
{
public:
	UnitAgent(Blackboard& b, sf::Vector2f v, std::list<Unit>& u);
	~UnitAgent();
	void execute();
private:
	Blackboard& m_blackboard;
	sf::Vector2f m_position;
	std::list<Unit>& m_enemies;
};

