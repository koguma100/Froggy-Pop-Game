#include "Tower.hpp"


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
	
	void balloonMovement() // moves all the balloons 
	{
		red.moveBalloon(checkpoints);
		blue.moveBalloon(checkpoints);
		green.moveBalloon(checkpoints);
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


				break;
			case sf::Event::MouseButtonPressed:
				if (ev.mouseButton.button == sf::Mouse::Left && control == ON) 
				{
					Tower copyFrog = frogs[0];
					frogs.push_back(copyFrog);
					control = OFF;
				}


				if (but1.isMouseOver(*window) && ev.mouseButton.button == sf::Mouse::Left && control == OFF)
				{
					control = ON;
				}
				break;
			}
		}
	}
	void update() // what actually happens in the game
	{
		pollEvents();

		balloonMovement();
		frogs[0].moveTower(*window, control);
		for (int x = 0; x < frogs.size() - 1; ++x)
		{
			frogs[x + 1].trackMouse(*window, red.getPosition());
		}
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
		for (int i = 0; i < checkpoints.size(); ++i)
		{
			window->draw(checkpoints[i]);
		}
		window->draw(red);
		window->draw(blue);
		window->draw(green);

		// draw towers
		if (control == ON)
			window->draw(frogs[0]);
		for (int x = 0; x < frogs.size() - 1; ++x)
		{
			window->draw(frogs[x + 1].getSightRadius());
			window->draw(frogs[x + 1]);
		}

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
	Balloon red,
			blue,
			green;

	// Checkpoints
	vector<Checkpoint> checkpoints;

	// Towers
	std::vector<Tower> frogs;
	control control = ON;

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
	void initTowers()
	{
		Tower frog = Tower(sf::Color::Black, 3, 1, 1, 100.f);
		frogs.push_back(frog);
	}
};