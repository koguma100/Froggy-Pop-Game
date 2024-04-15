#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "Game.h"

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
	}


	return 0;
}