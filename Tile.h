#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Unit.h"
#include "TileTypes.h"
class Tile
{
public:
	Tile() {};
	Tile(sf::Vector2f location, sf::Texture& tileset, sf::Texture& hR, sf::Texture& hB, int tSize)
		: m_gridLocation(location)
		, m_tileSize(tSize)
		, m_moveCost()
	{
		m_sprite.setTexture(&tileset);
		m_sprite.setSize(sf::Vector2f(m_tileSize, m_tileSize));
		m_highlightBlue.setTexture(&hB);
		m_highlightBlue.setSize(sf::Vector2f(m_tileSize, m_tileSize));
		m_highlightRed.setTexture(&hR);
		m_highlightRed.setSize(sf::Vector2f(m_tileSize, m_tileSize));
	};
	virtual ~Tile() {};
	virtual TileTypes getType() { return this->m_type; }
	virtual void setHighlight(bool b) {	m_highlighted = b; }
	virtual bool getHighlighted() {	return this->m_highlighted; }
	virtual int getCost() {	return this->m_moveCost; }
	virtual int getDefense() { return this->m_defense; }
	virtual void setUnit(Unit* u) { m_unit = u; }
	virtual void addEdge(sf::Vector2f v, Tile& tile) { m_adj.push_back({ v, &tile }); }
	virtual Unit* getUnit()	{ return m_unit; }
	virtual void setVisited(bool b)	{ visited = b; }
	virtual bool getVisited() {	return visited;	}
	virtual void setSCost(int sc) {	m_searchCost = sc; }
	virtual int getSCost() { return m_searchCost; }
	virtual Tile* getPrevious()	{ return m_previous; }
	virtual void setPrevious(Tile &t) {	m_previous = &t; }
	virtual void setEnemy(bool b) {	m_enemy = b; }
	virtual bool getEnemy() { return m_enemy; }

	std::list<std::pair<sf::Vector2f, Tile*>>& getAdj() { return m_adj; }

	virtual void setRect(sf::FloatRect r) { m_rect = r; }
	virtual sf::FloatRect getRect() { return m_rect; }

	virtual void render(sf::RenderWindow& window) {
		m_sprite.setPosition((m_gridLocation.x) * m_tileSize, (m_gridLocation.y) * m_tileSize);
		m_highlightBlue.setPosition((m_gridLocation.x) * m_tileSize, (m_gridLocation.y) * m_tileSize);
		m_highlightRed.setPosition((m_gridLocation.x) * m_tileSize, (m_gridLocation.y) * m_tileSize);
		window.draw(m_sprite);
		if (m_highlighted)
		{
			window.draw(m_highlightBlue);
		}
		else if (m_enemy)
		{
			window.draw(m_highlightRed);
		}
	}


protected:
	int m_moveCost;
	int m_defense;
	int m_tileSize;
	TileTypes m_type = TileTypes::Empty;
	bool m_highlighted = false;
	bool m_enemy = false;
	sf::Vector2f m_gridLocation;
	sf::RectangleShape m_sprite, m_highlightSprite, m_highlightRed, m_highlightBlue;
private:
	//sf::RectangleShape* m_texture;
	bool visited;
	int m_searchCost;
	Unit* m_unit = nullptr;
	std::list<std::pair<sf::Vector2f, Tile*>> m_adj;
	sf::FloatRect m_rect;
	Tile* m_previous;
};