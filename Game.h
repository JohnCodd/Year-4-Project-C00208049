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
	double windowWidth = 1366;
	double windowHeight = 768;
	int mapWidth = 15;
	int mapHeight = 15;
	float tileSize = 64;
	sf::RenderWindow m_window;
	sf::View gameView, backView;
	sf::Font m_font;
	Map m_map;
};