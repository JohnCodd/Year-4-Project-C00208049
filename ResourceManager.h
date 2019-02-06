#pragma once
#include <map>
#include <string>
#include "SFML/Graphics.hpp"
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	void loadTexture(std::string name, std::string path);
	void loadFont(std::string name, std::string path);
	sf::Texture& getTexture(std::string name);
	sf::Font& getFont(std::string name);
private:
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
};

