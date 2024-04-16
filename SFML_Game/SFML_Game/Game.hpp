#include "Balloon.hpp"
#include "Tower.hpp"
#include "Button.hpp"

// Class that acts as a game engine: Wrapper Class
class Game
{
public:
	// Constructors / Destructors
	Game()
	{
		initVariables();
		initWindow();
		initBackground();
		initBalloons();
		initTowers();
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

	void balloonMovement() // updates all the balloons movements
	{
		red.moveBalloon();
		blue.moveBalloon();
		green.moveBalloon();
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
				if (ev.key.code == sf::Keyboard::Escape) // closing window
				{
					window->close();
				}


				if (ev.key.code == sf::Keyboard::O) // changing control
				{
					if (control == ON)
					{
						control = OFF;
					}
					else
					{
						control = ON;
					}
				}

				break;
			case sf::Event::MouseButtonPressed:
				if (ev.mouseButton.button == sf::Mouse::Left && control == ON)
				{
					Tower copyFrog = frogs[0];
					frogs.push_back(copyFrog);
				}
				break;
			}
		}
	}
	void update() // what actually happens in the game
	{
		pollEvents();

		balloonMovement();
		frogs[0].moveTower(window, control);
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
		window->draw(background);

		// draw balloons
		window->draw(red);
		window->draw(blue);
		window->draw(green);

		// draw towers
		if (control == ON)
		window->draw(frogs[0]);
		for (int x = 0; x < frogs.size() - 1; ++x)
		{
			window->draw(frogs[x + 1]);
		}

		// draw menu
		window->draw(but1);
	
		window->display(); // updates the new frame 
	}

private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Game Objects
	// Balloons
	Balloon red,
			blue,
			green;

	// Towers
	std::vector<Tower> frogs;
	control control = ON;

	// Menus
	Button but1;

	// Map
	sf::Texture backgroundTexture;
	sf::Sprite background;

	// private functions
	void initVariables()
	{
		window = nullptr;
	}
	void initWindow()
	{
		videoMode.height = 525;
		videoMode.width = 825;

		window = new sf::RenderWindow(videoMode, "Project F");

		window->setFramerateLimit(144);
	}
	void initBackground()
	{
		if (!backgroundTexture.loadFromFile("Textures/MonkeyMeadow.png"))
		{
			cout << "Image File not found" << endl;
		}

		background.setTexture(backgroundTexture);
	}
	void initBalloons()
	{
		red = Balloon(1, 20, Vector2f(100, 100));
		blue = Balloon(2, 20, Vector2f(100, 100));
		green = Balloon(3, 20, Vector2f(100, 100));
	}
	void initTowers()
	{
		Tower frog = Tower(sf::Color::Black, 3, 1, 1);
		frogs.push_back(frog);
	}

};