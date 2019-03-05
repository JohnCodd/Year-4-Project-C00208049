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
		: gridLocation(location)
		, tileSize(tSize)
		, moveCost()
	{
		sprite.setTexture(&tileset);
		sprite.setSize(sf::Vector2f(tileSize, tileSize));
		highlightBlue.setTexture(&hB);
		highlightBlue.setSize(sf::Vector2f(tileSize, tileSize));
		highlightRed.setTexture(&hR);
		highlightRed.setSize(sf::Vector2f(tileSize, tileSize));
	};
	virtual ~Tile() {};
	virtual TileTypes getType() { return this->type; }
	virtual void setHighlight(bool b) {	highlighted = b; }
	virtual bool getHighlighted() {	return this->highlighted; }
	virtual int getCost() {	return this->moveCost; }
	virtual int getDefense() { return this->defense; }
	virtual void setUnit(Unit* u) { m_unit = u; }
	virtual void addEdge(sf::Vector2f v, Tile& tile) { adj.push_back({ v, &tile }); }
	virtual Unit* getUnit()	{ return m_unit; }
	virtual void setVisited(bool b)	{ visited = b; }
	virtual bool getVisited() {	return visited;	}
	virtual void setSCost(int sc) {	searchCost = sc; }
	virtual int getSCost() { return searchCost; }
	virtual Tile* getPrevious()	{ return m_previous; }
	virtual void setPrevious(Tile &t) {	m_previous = &t; }
	virtual void setEnemy(bool b) {	enemy = b; }
	virtual bool getEnemy() { return enemy; }

	std::list<std::pair<sf::Vector2f, Tile*>>& getAdj() { return adj; }

	virtual void setRect(sf::FloatRect r) { rect = r; }
	virtual sf::FloatRect getRect() { return rect; }

	virtual void render(sf::RenderWindow& window) {
		sprite.setPosition((gridLocation.x) * tileSize, (gridLocation.y) * tileSize);
		highlightBlue.setPosition((gridLocation.x) * tileSize, (gridLocation.y) * tileSize);
		highlightRed.setPosition((gridLocation.x) * tileSize, (gridLocation.y) * tileSize);
		window.draw(sprite);
		if (highlighted)
		{
			window.draw(highlightBlue);
		}
		else if (enemy)
		{
			window.draw(highlightRed);
		}
	}


protected:
	int moveCost;
	int defense;
	int tileSize;
	TileTypes type = TileTypes::Empty;
	bool highlighted = false;
	bool enemy = false;
	sf::Vector2f gridLocation;
	sf::RectangleShape sprite;
	sf::RectangleShape highlightSprite;
	sf::RectangleShape highlightRed;
	sf::RectangleShape highlightBlue;
private:
	//sf::RectangleShape* m_texture;
	bool visited;
	int searchCost;
	Unit* m_unit = nullptr;
	std::list<std::pair<sf::Vector2f, Tile*>> adj;
	sf::FloatRect rect;
	Tile* m_previous;
};