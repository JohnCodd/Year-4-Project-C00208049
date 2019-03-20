#pragma once
#include "Blackboard.h"
class UnitAgent
{
public:
	UnitAgent(Blackboard& b, sf::Vector2f v);
	~UnitAgent();
	void execute();
private:
	Blackboard& m_blackboard;
	sf::Vector2f m_position;
};

