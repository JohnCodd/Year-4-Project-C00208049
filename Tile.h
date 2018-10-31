#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Tile
{
public:
	Tile() {};
	~Tile() {};
	virtual std::string getType()
	{
		return this->type;
	}
	virtual void highlight()
	{
		if (highlighted == true)
		{
			highlighted = false;
		}
		else
		{
			highlighted = true;
		}
	}
	virtual bool getHighlighted()
	{
		return this->highlighted;
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
	bool highlighted = false;
private:
	//sf::RectangleShape* m_texture;
};