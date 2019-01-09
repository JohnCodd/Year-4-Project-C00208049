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

	virtual void addEdge(sf::Vector2f v, Tile& tile)
	{
		adj.push_back({ v, &tile });
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
	virtual Tile* getPrevious()
	{
		return m_previous;
	}
	virtual void setPrevious(Tile &t)
	{
		m_previous = &t;
	}
	virtual void setEnemy(bool b)
	{
		enemy = b;
	}
	virtual bool getEnemy() { return enemy; }

	std::list<std::pair<sf::Vector2f, Tile*>>& getAdj() { return adj; };

protected:
	int moveCost;
	float defense;
	std::string type;
	bool highlighted = false;
	bool enemy = false;
private:
	//sf::RectangleShape* m_texture;
	bool visited;
	int searchCost;
	Unit* m_unit = nullptr;
	std::list<std::pair<sf::Vector2f, Tile*>> adj;
	Tile* m_previous;
};