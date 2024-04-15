#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>


using std::cout;
using std::cin;
using std::endl;

// Class that acts as a game engine: Wrapper Class
class Game
{
public:
	// Constructors / Destructors
	Game()
	{
		initVariables();
		initWindow();
		initEnemies();
	}
	~Game()
	{
		delete window;
	}

	// Accessors
	const bool running() const
	{
		return window->isOpen();
	}

	// Other Functions
	void pollEvents() // What happens in the game
	{
		while (window->pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window->close();
				break;

			case sf::Event::KeyPressed: // tells the program that the user pressed the escape key
				if (ev.key.code == sf::Keyboard::Escape)
				{
					window->close();
				}
				break;
			}
		}
	}
	void update() // what actually happens in the game
	{
		pollEvents();

	}
	void render() // graphics
	{
		/*
			- clear old frame
			- render obejcts
			- display frame in window

			Renders the game objects
		*/

		window->clear(); // clears the screen

		// Draw Game // 
		window->draw(enemy); 

		window->display(); // updates the new frame 
	}

private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Game Objects
	sf::RectangleShape enemy;

	// private functions
	void initVariables()
	{
		window = nullptr;
	}
	void initWindow()
	{
		videoMode.height = 650;
		videoMode.width = 800;

		window = new sf::RenderWindow(videoMode, "My First Game");

		window->setFramerateLimit(144);
	}
	void initEnemies() // sets the size of the square
	{
		enemy.setPosition(350.f, 225.f);
		enemy.setSize(sf::Vector2f(100.f, 100.f));
		//enemy.setScale(sf::Vector2f(.5f, .5f));
		enemy.setFillColor(sf::Color::Cyan);
		enemy.setOutlineColor(sf::Color::Green);
		enemy.setOutlineThickness(1.f);
	}
};