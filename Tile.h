#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Unit.h"
class Tile
{
public:
	Tile() {};
	~Tile() {};
	virtual std::string getType()
	{
		return this->type;
	}
	virtual void setHighlight(bool b)
	{
		highlighted = b;
	}
	virtual bool getHighlighted()
	{
		return this->highlighted;
	}
	virtual int getCost()
	{
		return this->moveCost;
	}
	virtual void setUnit(Unit* u)
	{
		m_unit = u;
	}

	virtual void addEdge(Tile& tile)
	{
		adj.push_back(&tile);
	}

	virtual Unit* getUnit()
	{
		return m_unit;
	}

	virtual void setVisited(bool b)
	{
		visited = b;
	}

	virtual bool getVisited()
	{
		return visited;
	}
	
	virtual void setSCost(int sc)
	{
		searchCost = sc;
	}
	virtual int getSCost()
	{
		return searchCost;
	}

	std::list<Tile*>& getAdj() { return adj; };

protected:
	int moveCost;
	float defense;
	std::string type;
	bool highlighted = false;
private:
	//sf::RectangleShape* m_texture;
	bool visited;
	int searchCost;
	Unit* m_unit = nullptr;
	std::list<Tile*> adj;
	Tile* m_previous;
};