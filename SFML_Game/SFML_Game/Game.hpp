#include "Balloon.hpp"

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
		red.moveBalloon();
		blue.moveBalloon();
		green.moveBalloon();

		window->clear(); // clears the screen

		// Draw Game // 
		window->draw(background);

		window->draw(red);
		window->draw(blue);
		window->draw(green);

		window->display(); // updates the new frame 
	}

private:
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Game Objects
	Balloon red,
			blue,
			green;

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
		videoMode.height = 650;
		videoMode.width = 800;

		window = new sf::RenderWindow(videoMode, "My First Game");

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

};