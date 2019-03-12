#include "Game.h"

static double const MS_PER_UPDATE = 10.0;

Game::Game()
	: m_window(sf::VideoMode(windowWidth, windowHeight, 32), "Square Wars", sf::Style::Default), m_rManager(),
		 m_map(tileSize, playerTurn, m_rManager)
	
{
	m_window.setFramerateLimit(60);
	m_rManager.loadFont("times", "./Resources/Fonts/times.ttf");
	m_map.loadMap("./Resources/Maps/Map1.json");
	gameView.setSize(sf::Vector2f(20 * tileSize, 15 * tileSize));
	gameView.setCenter(sf::Vector2f(((20 * tileSize) / 2) - tileSize, ((15 * tileSize) / 2) - tileSize));
	gameWindowWidth = (20 * tileSize) / windowWidth;
	sideBarX = windowWidth * gameWindowWidth;
	gameView.setViewport(sf::FloatRect(0.0f, 0.0f, gameWindowWidth, 1.0f));
	backView.setSize(windowWidth, windowHeight);
	backView.setCenter(windowWidth / 2, windowHeight / 2);
	backView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	m_font = m_rManager.getFont("times");
	turnButton = Button(sf::Vector2f(sideBarX + 50, 300), sf::Vector2f(100, 100), m_font, "End Turn");
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
				m_map.leftclickMap(m_window.mapPixelToCoords(sf::Vector2i(mouse)));
				if (turnButton.getRect().intersects(sf::FloatRect(sf::Vector2f(mouse), sf::Vector2f(2, 2))))
				{
						
					playerTurn++;
					if (playerTurn > maxPlayers)
					{
						playerTurn = 1;
					}
					m_map.turnUpkeep();
						
				}
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
				m_map.fButton(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)), m_rManager);
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				if (gameView.getCenter().x < (m_map.getBorder().width - (gameView.getSize().x / 2) + tileSize))
				{
					gameView.setCenter(gameView.getCenter().x + tileSize, gameView.getCenter().y);
				}
			}
			if (event.key.code == sf::Keyboard::Left)
			{
				if (gameView.getCenter().x > (gameView.getSize().x / 2) - tileSize)
				{
					gameView.setCenter(gameView.getCenter().x - tileSize, gameView.getCenter().y);
				}
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				if (gameView.getCenter().y > (gameView.getSize().y / 2) - tileSize)
				{
					gameView.setCenter(gameView.getCenter().x, gameView.getCenter().y - tileSize);
				}
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				if (gameView.getCenter().y < (m_map.getBorder().height - (gameView.getSize().y / 2) + tileSize))
				{
					gameView.setCenter(gameView.getCenter().x, gameView.getCenter().y + tileSize);
				}
			}
		}
	}
}

void Game::update(double dt)
{
	sf::Vector2f mousePosition = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	if (mousePosition.x < sideBarX && mousePosition.x > 0 && mousePosition.y > 0 && mousePosition.y < mapHeight * tileSize)
	{
		sf::Vector2f mapKey = m_map.convertToKey(sf::Vector2f(mousePosition));
		if (m_map.checkTile(mapKey))
		{
			if (&m_map.getUnit(mapKey) != nullptr)
			{
				unitHighlighted = true;
				unitHealth.setString("Health: " + std::to_string(m_map.getUnit(mapKey).getHealth()));
				unitMoves.setString("Moves: " + std::to_string(m_map.getUnit(mapKey).getRemainingMoves()));
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
	m_map.update(dt);
}

void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_window.setView(backView);
	sf::RectangleShape sideBar = sf::RectangleShape(sf::Vector2f(windowWidth - sideBarX, windowHeight));
	sideBar.setPosition(sideBarX, 0);
	sideBar.setFillColor(sf::Color(79, 48, 15));
	std::string pText = "Player: " + std::to_string(static_cast<int>(playerTurn));
	m_window.draw(sideBar);
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