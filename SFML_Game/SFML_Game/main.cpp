#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "Game.hpp"

int main()
{
	// Init Game Engine
	Game game;

	//Game Loop
	while (game.running())
	{
		// Update
		game.update();

		// Render
		game.render();
		//cout << sf::Mouse::getPosition().x << ", " << sf::Mouse::getPosition().y << endl;
	}


	return 0;
}