#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Tile
{
public:
	Tile() {};
	~Tile() {};
	virtual void setType(std::string type) {
		this->type = type;
	}
	virtual std::string getType()
	{
		return this->type;
	}
	//virtual void setTexture(sf::RectangleShape* texture) {
	//	this->m_texture = texture;
	//};
	//virtual sf::RectangleShape getTexture()
	//{
	//	return *this->m_texture;
	//}

protected:
	int moveCost;
	float defense;
	std::string type;
private:
	//sf::RectangleShape* m_texture;
};