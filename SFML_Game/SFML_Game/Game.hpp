
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
		initCheckpoints();
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

	void balloonMovement() // moves all the balloons 
	{
		red.moveBalloon(checkpoints);
		blue.moveBalloon(checkpoints);
		green.moveBalloon(checkpoints);
	}

	void update() // what actually happens in the game
	{
		pollEvents();

		balloonMovement();
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

		for (int i = 0; i < checkpoints.size(); ++i)
		{
			window->draw(checkpoints[i]);
		}
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

	vector<Checkpoint> checkpoints;

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
		red = Balloon(1, 15, Vector2f(0, 210));
		blue = Balloon(2, 15, Vector2f(0, 210));
		green = Balloon(3, 15, Vector2f(0, 210));
	}

	void initCheckpoints()
	{
		checkpoints.push_back(Checkpoint(UP, Vector2f(30, 30), Vector2f(430, 200)));
		checkpoints.push_back(Checkpoint(LEFT, Vector2f(30, 30), Vector2f(400, 50)));
		checkpoints.push_back(Checkpoint(DOWN, Vector2f(30, 30), Vector2f(220, 80)));
		checkpoints.push_back(Checkpoint(LEFT, Vector2f(30, 30), Vector2f(240, 445)));
		checkpoints.push_back(Checkpoint(UP, Vector2f(30, 30), Vector2f(90, 410)));

		checkpoints.push_back(Checkpoint(RIGHT, Vector2f(30, 30), Vector2f(130, 260)));
		checkpoints.push_back(Checkpoint(UP, Vector2f(30, 30), Vector2f(540, 300)));
		checkpoints.push_back(Checkpoint(RIGHT, Vector2f(30, 30), Vector2f(500, 140)));
		checkpoints.push_back(Checkpoint(DOWN, Vector2f(30, 30), Vector2f(640, 170)));
		checkpoints.push_back(Checkpoint(LEFT, Vector2f(30, 30), Vector2f(610, 400)));
		checkpoints.push_back(Checkpoint(DOWN, Vector2f(30, 30), Vector2f(325, 370)));
	}
};