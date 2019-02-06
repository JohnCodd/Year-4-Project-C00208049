#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
	//loadTexture("tileset", "./Resources/Tilesets/tileset.png");
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::loadTexture(std::string name, std::string path)
{
	sf::Texture t;
	if (!t.loadFromFile(path))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	textures[name] = std::move(t);
}

void ResourceManager::loadFont(std::string name, std::string path)
{
	sf::Font f;
	if (!f.loadFromFile(path))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	fonts[name] = std::move(f);
}

sf::Texture& ResourceManager::getTexture(std::string name)
{
	return textures[name];
}

sf::Font & ResourceManager::getFont(std::string name)
{
	return fonts[name];
}