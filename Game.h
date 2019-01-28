#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Map.h"
#include "Button.h"

class Game
{
public:
	Game();
	~Game();
	void run();
protected:
	void update(double dt);
	void render();
	void processEvents();
	double windowWidth = 1620;
	double windowHeight = 960;
	int mapWidth = 20;
	int mapHeight = 15;
	int tileSize = 64;
	int playerTurn = 1;
	int maxPlayers = 2;
	sf::RenderWindow m_window;
	sf::View gameView, backView, sideView;
	sf::Font m_font;
	sf::Text currentTurn, unitHealth, unitMoves, terrainDefense, terrainCost;
	bool unitHighlighted = false;
	bool tileHighlighted = false;
	float gameWindowWidth;
	float sideBarX;
	Map m_map;
	Button turnButton;
};