#include "Game.h"

static double const MS_PER_UPDATE = 10.0;

Game::Game()
	: m_window(sf::VideoMode(windowWidth, windowHeight, 32), "Square Wars", sf::Style::Default), m_map(mapWidth, mapHeight, tileSize)
{
	m_window.setFramerateLimit(60);
	gameView.setSize(sf::Vector2f(mapWidth * tileSize, mapHeight * tileSize));
	gameView.setCenter(sf::Vector2f((mapWidth * tileSize) / 2, (mapHeight * tileSize) / 2));
	gameView.setViewport(sf::FloatRect(0.20f, 0.0f, windowHeight / windowWidth, 1.0f));
	if (!m_font.loadFromFile("./times.ttf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
}

Game::~Game()
{

}

void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;

				sf::FloatRect gameMap = sf::FloatRect(windowWidth * gameView.getViewport().left, 0, windowWidth * gameView.getViewport().width, windowHeight);
				sf::Vector2f mouse = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				//if (mouse.x > gameMap.left && mouse.x < gameMap.left + gameMap.width)
				//{
				//	sf::Vector2f mapSize = sf::Vector2f(mapWidth * tileSize, mapHeight * tileSize);
				//	sf::Vector2f windowMouse = sf::Vector2f(mouse.x - gameMap.left, mouse.y - gameMap.top);
				//	sf::Vector2f conversion = sf::Vector2f(windowHeight / mapSize.x, windowHeight / mapSize.y);
				//	//sf::Vector2f mapMouse = sf::Vector2f(windowMouse.x * conversion.x, windowMouse.y * conversion.y);
				//	sf::Vector2f mapMouse = m_window.mapPixelToCoords(sf::Vector2i(mouse));
				//	std::cout << "In map" << std::endl;
					m_map.leftclickMap(m_window.mapPixelToCoords(sf::Vector2i(mouse)));
				//}
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				m_map.rightclick(event);
			}
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::F)
			{
				m_map.fButton(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
			}
		}
	}
}

void Game::update(double dt)
{
}

void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	//Experimental game view
	//m_window.setView(gameView);
	sf::Text name = sf::Text("Square Wars", m_font, 30);
	name.setPosition(100, 100);
	m_map.render(m_window, tileSize);
	//m_window.draw(name);
	m_window.display();
}