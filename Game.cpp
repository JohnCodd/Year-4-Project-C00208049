#include "Game.h"

static double const MS_PER_UPDATE = 10.0;

Game::Game()
	: m_window(sf::VideoMode(windowWidth, windowHeight, 32), "Square Wars", sf::Style::Default), m_map(mapWidth, mapHeight, tileSize, playerTurn)
	
{
	m_window.setFramerateLimit(60);
	gameView.setSize(sf::Vector2f(20 * tileSize, 15 * tileSize));
	gameView.setCenter(sf::Vector2f((20 * tileSize) / 2, (15 * tileSize) / 2));
	//float sideWidth = windowWidth - windowHeight;
	//sideView.setSize(sideWidth, windowHeight);
	//sideView.setCenter(sideWidth / 2, windowHeight);
	gameWindowWidth = (20 * tileSize) / windowWidth;
	sideBarX = windowWidth * gameWindowWidth;
	//sideView.setViewport(sf::FloatRect(gameWindowWidth, 1.0f, windowWidth - gameWindowWidth, 1.0f));
	turnButton = Button(sf::Vector2f(sideBarX + 50, 300), sf::Vector2f(100, 100), m_font, "End Turn");
	gameView.setViewport(sf::FloatRect(0.0f, 0.0f, gameWindowWidth, 1.0f));
	backView.setSize(windowWidth, windowHeight);
	backView.setCenter(windowWidth / 2, windowHeight / 2);
	backView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	if (!m_font.loadFromFile("./times.ttf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	std::string pText = "Player: " + std::to_string(static_cast<int>(playerTurn));
	currentTurn = sf::Text(pText, m_font, 30);
	currentTurn.setPosition((sideBarX) + 50, 50);
	unitHealth = sf::Text("", m_font, 30);
	unitHealth.setPosition(sideBarX + 20, windowHeight - 200);
	unitMoves = sf::Text("", m_font, 30);
	unitMoves.setPosition(sideBarX + 20, windowHeight - 170);
	terrainDefense = sf::Text("", m_font, 30);
	terrainDefense.setPosition(sideBarX + 170, windowHeight - 200);
	terrainCost = sf::Text("", m_font, 30);
	terrainCost.setPosition(sideBarX + 170, windowHeight - 170);
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
				/*if (mouse.x <= 1280)
				{*/
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
				if (turnButton.getRect().intersects(sf::FloatRect(m_window.mapPixelToCoords(sf::Vector2i(mouse)), sf::Vector2f(2, 2))))
				{
						
					playerTurn++;
					if (playerTurn > maxPlayers)
					{
						playerTurn = 1;
					}
						
				}
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
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
	if (mousePosition.x < sideBarX)
	{
		sf::Vector2f mapKey = m_map.convertToKey(sf::Vector2f(mousePosition));
		if (m_map.checkTile(mapKey))
		{
			if (&m_map.getUnit(mapKey) != nullptr)
			{
				unitHighlighted = true;
				unitHealth.setString("Health: " + std::to_string(m_map.getUnit(mapKey).getHealth()));
				unitMoves.setString("Moves: " + std::to_string(m_map.getUnit(mapKey).getMoves()));
			}
			else
			{
				unitHighlighted = false;
			}
			tileHighlighted = true;
			terrainDefense.setString("Defense: " + std::to_string(m_map.getTile(mapKey).getDefense()));
			terrainCost.setString("Move Cost: " + std::to_string(m_map.getTile(mapKey).getCost()));
		}
	}
	else
	{
		tileHighlighted = false;
	}
}

void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_window.setView(backView);

	std::string pText = "Player: " + std::to_string(static_cast<int>(playerTurn));
	currentTurn.setString(pText);
	m_window.draw(currentTurn);
	turnButton.render(m_window);
	if (unitHighlighted)
	{
		m_window.draw(unitHealth);
		m_window.draw(unitMoves);
	}
	if (tileHighlighted)
	{
		m_window.draw(terrainDefense);
		m_window.draw(terrainCost);
	}
	//Experimental game view
	m_window.setView(gameView);
	m_map.render(m_window, tileSize);
	m_window.display();
}