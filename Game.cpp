#include "Game.h"

static double const MS_PER_UPDATE = 10.0;

Game::Game()
	: m_window(sf::VideoMode(windowWidth, windowHeight, 32), "Square Wars", sf::Style::Default), m_map(60, 20)
{
	m_window.setFramerateLimit(60);
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
	}
}

void Game::update(double dt)
{
}

void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	sf::Text name = sf::Text("Square Wars", m_font, 30);
	name.setPosition(100, 100);
	m_map.render(m_window);
	m_window.draw(name);
	m_window.display();
}