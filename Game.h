#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Map.h"

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
	sf::RenderWindow m_window;
	sf::View gameView;
	sf::Font m_font;
	Map m_map;
};