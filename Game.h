#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

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
	sf::RenderWindow m_window;
	sf::Font m_font;
};