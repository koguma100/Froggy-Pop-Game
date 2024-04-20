#include "Menu.hpp"

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
		initMenu();
		lives = 100;
		eco = 500;
		numOfBloons = 0;
		round = 1;
		elapsed_time = clock.getElapsedTime();
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
		for (int i = 0; i < bloons.size(); ++i)
		{
			bloons[i]->moveBalloon(checkpoints, lives, eco);
		}
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
		sf::Time normal_rush_time = sf::milliseconds(500);
		sf::Time grouped_rush_time = sf::milliseconds(100);

		pollEvents();
		
		elapsed_time += clock.restart();

		if (round == 1)	// will probably make a round function to make update less cluttered
		{
			// 15 red spaced ruch
			if (numOfBloons < 15 && elapsed_time >= normal_rush_time)
			{
				spawnBalloon(1, bloons);
				numOfBloons++;
				elapsed_time = sf::milliseconds(0);
			}

			// 15 red bloon group rush

			if ((numOfBloons >= 15 && numOfBloons < 30) && elapsed_time >= grouped_rush_time)
			{
				spawnBalloon(1, bloons);
				numOfBloons++;
				elapsed_time = sf::milliseconds(0);
			}

			if ((numOfBloons >= 30 && numOfBloons < 45) && elapsed_time >= normal_rush_time)
			{
				spawnBalloon(2, bloons);
				numOfBloons++;
				elapsed_time = sf::milliseconds(0);
			}

			if (roundEnded(bloons))
			{
				emptyBloons(bloons);
			}
		}
		// basic 15 bloon normal rush
		
		
		balloonMovement();
		
		// frog updates
		// track mouse
		frogs[0].moveTower(*window, control);

		for (int x = 0; x < frogs.size() - 1; ++x)
		{

			if (frogs[x + 1].getBloonInSight() != -1 && bloons[frogs[x + 1].getBloonInSight()]->getType() != 0
				&& frogs[x + 1].checkInRadius(bloons[frogs[x + 1].getBloonInSight()]->getPosition()))
			{
				frogs[x + 1].findRotateDeg(bloons[frogs[x + 1].getBloonInSight()]->getPosition());
			} 
			else
			{
				frogs[x + 1].setBloonInSight(-1);
				bool bloonFound = false;
				for (int i = 0; i < bloons.size() && !bloonFound; ++i)
				{
					if (frogs[x + 1].checkInRadius(bloons[i]->getPosition()))
					{
						bloonFound = true;
						frogs[x + 1].setBloonInSight(i);
						frogs[x + 1].findRotateDeg(bloons[i]->getPosition());
					}
				}
			}
			if (bloons.size() > 0 && frogs[x + 1].checkInRadius(bloons[0]->getPosition()))
			{
				frogs[x + 1].findRotateDeg(bloons[0]->getPosition());
			}
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

		for (int i = 0; i < bloons.size(); ++i)
		{
			//cout << bloons[i].getPosition().x << endl;
			window->draw(*bloons[i]);
		}

		// draw towers
		if (control == ON)
			window->draw(frogs[0]);
		for (int x = 0; x < frogs.size() - 1; ++x)
		{
			window->draw(frogs[x + 1].getSightRadius());
			window->draw(frogs[x + 1]);
		}

		window->draw(but1);

		// draw menu
		sideMenu.drawmenu(window, lives, eco);

		window->display(); // updates the new frame 
	}

private:
	// Variables
	int lives, eco, numOfBloons, round;

	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Game Time 
	sf::Clock clock;
	sf::Time elapsed_time;

	// Game Objects
	vector<Balloon*> bloons;

	// Checkpoints
	vector<Checkpoint> checkpoints;

	// Towers
	std::vector<Tower> frogs;
	control control = ON;

	Button but1;

	// Map
	sf::Texture backgroundTexture;
	sf::Sprite background;

	//Menu
	Menu sideMenu;

	// private functions
	void initVariables()
	{
		window = nullptr;
	}
	void initWindow()
	{
		videoMode.height = 900;
		videoMode.width = 1800; //825

		window = new sf::RenderWindow(videoMode, "Project F");

		window->setFramerateLimit(144);

	}

	void initMenu()
	{
		sideMenu = Menu(Vector2f(1525, 0), Vector2f(375, 900));

		//Heart Picture

		if (!sideMenu.getHeart().loadFromFile("Textures/Heart.png", sf::IntRect(0, 0, 80, 80)))
		{
			cout << "Image File Heart not found" << endl;
		}

		sideMenu.getSprite().setTexture(sideMenu.getHeart());

		sideMenu.getSprite().setPosition(Vector2f(15, 15));

		sideMenu.getSprite().setScale(.5, .5);

		//Money Picutre

		if (!sideMenu.getCoins().loadFromFile("Textures/Money.png", sf::IntRect(0, 0, 80, 80)))
		{
			cout << "Image File Money not found" << endl;
		}

		sideMenu.getGold().setTexture(sideMenu.getCoins());

		sideMenu.getGold().setPosition(Vector2f(105, 15));

		sideMenu.getGold().setScale(.5, .5);


		//Lives Text

		if (!sideMenu.getFont().loadFromFile("Fonts/Font.ttf"))
		{
			cout << "Font File Font not found" << endl;
		}

		sideMenu.getLivesText().setFont(sideMenu.getFont());

		sideMenu.getLivesText().setString("299");

		sideMenu.getLivesText().setCharacterSize(24);

		sideMenu.getLivesText().setFillColor(sf::Color::White);

		sideMenu.getLivesText().setPosition(Vector2f(55, 15));

		//Coin Text

		sideMenu.getMoneyeco().setFont(sideMenu.getFont());

		sideMenu.getMoneyeco().setString("499");

		sideMenu.getMoneyeco().setCharacterSize(24);

		sideMenu.getMoneyeco().setFillColor(sf::Color::White);

		sideMenu.getMoneyeco().setPosition(Vector2f(145, 15));

	}

	void initBackground()
	{
		if (!backgroundTexture.loadFromFile("Textures/MonkeyMeadow.png"))
		{
			cout << "Image File not found" << endl;
		}

		background.setTexture(backgroundTexture);
		background.setScale(1.85f, 1.70f);
	}

	void initBalloons()
	{
	
	}

	void initCheckpoints()
	{
		checkpoints.push_back(Checkpoint(UP, Vector2f(30, 30), Vector2f(770, 350)));
		checkpoints.push_back(Checkpoint(LEFT, Vector2f(30, 30), Vector2f(720, 125)));
		checkpoints.push_back(Checkpoint(DOWN, Vector2f(30, 30), Vector2f(460, 140)));
		checkpoints.push_back(Checkpoint(LEFT, Vector2f(30, 30), Vector2f(480, 740)));
		checkpoints.push_back(Checkpoint(UP, Vector2f(30, 30), Vector2f(210, 710)));

		checkpoints.push_back(Checkpoint(RIGHT, Vector2f(30, 30), Vector2f(230, 475)));
		checkpoints.push_back(Checkpoint(UP, Vector2f(30, 30), Vector2f(975, 500)));
		checkpoints.push_back(Checkpoint(RIGHT, Vector2f(30, 30), Vector2f(940, 255)));
		checkpoints.push_back(Checkpoint(DOWN, Vector2f(30, 30), Vector2f(1170, 300)));
		checkpoints.push_back(Checkpoint(LEFT, Vector2f(30, 30), Vector2f(1140, 670)));
		checkpoints.push_back(Checkpoint(DOWN, Vector2f(30, 30), Vector2f(630, 640)));
	}
	void initTowers()
	{
		Tower frog = Tower(sf::Color::Black, 3, 1, 150.f);
		frogs.push_back(frog);
	}
};