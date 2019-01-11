#pragma once
#include "SFML/Graphics.hpp"
#include <string>
class Button
{
public:
	Button(sf::Vector2f v, sf::Vector2f size, sf::Font& font, std::string label);
	~Button();
	sf::FloatRect getRect();
	void render(sf::RenderWindow & window);
private:
	sf::FloatRect collider;
	sf::RectangleShape m_rect;
	sf::Font* m_font;
	std::string text;
	sf::Text buttonLabel;
};

