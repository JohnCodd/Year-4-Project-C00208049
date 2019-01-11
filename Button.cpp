#include "Button.h"



Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Font& font, std::string label)
{
	collider = sf::FloatRect(position, size);
	m_rect.setPosition(position);
	m_rect.setSize(size);
	m_rect.setFillColor(sf::Color::Green);
	m_rect.setOutlineColor(sf::Color::Yellow);
	m_rect.setOutlineThickness(2);
	m_font = &font;
	text = label;
	buttonLabel = sf::Text(text, *m_font, 20);
	sf::FloatRect textRect = buttonLabel.getLocalBounds();
	buttonLabel.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
		buttonLabel.setPosition(sf::Vector2f(position.x + (size.x / 2), position.y + (size.y / 2)));
}


Button::~Button()
{
}

sf::FloatRect Button::getRect()
{
	return collider;
}

void Button::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
	window.draw(buttonLabel);
}
