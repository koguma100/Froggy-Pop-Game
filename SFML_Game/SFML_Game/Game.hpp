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
		initTexture();
		initTowers();
		initmenu();
		initbutton();
		lives = 100;
		eco = 500;
		numOfBloons = 0;
		roundcount = 1;
		towerselected = DART;
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
			bloons[i]->moveBalloon(checkpoints, lives);
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

					sf::RenderWindow thing;
					sf::Mouse::getPosition(thing);

					sf::Vector2f mousePosition = thing.mapPixelToCoords(sf::Mouse::getPosition(thing));

					switch (towerselected)
					{
					case DART:
						copyFrog = frogs[0];
						/*dFrogSprite.setTexture(dartFrogTexture);
						dFrogSprite.setPosition(mousePosition);*/
						break;
					case NINJA:
						copyFrog = frogs[1];
						/*nFrogSprite.setTexture(ninjaFrogTexture);
						nFrogSprite.setPosition(mousePosition);*/
						break;
					case TACK:
						copyFrog = frogs[2];
						/*tFrogSprite.setTexture(tackFrogTexture);
						tFrogSprite.setPosition(mouse);*/
						break;
					case WIZARD:
						copyFrog = frogs[3];
						/*wFrogSprite.setTexture(wizardFrogTexture);
						wFrogSprite.setPosition(mousePosition);*/
						break;
					default:
						copyFrog = frogs[0];
						break;
					}
					frogs.push_back(copyFrog);
					
					control = OFF;
				}


				if (dart.isMouseOver(*window) && ev.mouseButton.button == sf::Mouse::Left && control == OFF)
				{
					control = ON;
					towerselected = DART;
				}
				else if (ninja.isMouseOver(*window) && ev.mouseButton.button == sf::Mouse::Left && control == OFF)
				{
					control = ON;
					towerselected = NINJA;
				}
				else if (tack.isMouseOver(*window) && ev.mouseButton.button == sf::Mouse::Left && control == OFF)
				{
					control = ON;
					towerselected = TACK;
				}
				else if (wizard.isMouseOver(*window) && ev.mouseButton.button == sf::Mouse::Left && control == OFF)
				{
					control = ON;
					towerselected = WIZARD;
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

		if (roundcount == 1)	// will probably make a round function to make update less cluttered
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
		switch (towerselected)
		{
		case DART:
			frogs[0].moveTower(*window, control);
			break;
		case NINJA:
			frogs[1].moveTower(*window, control);
			break;
		case TACK:
			frogs[2].moveTower(*window, control);
			break;
		case WIZARD:
			frogs[3].moveTower(*window, control);
			break;
		default:
			frogs[0].moveTower(*window, control);
			break;
		}

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

		 //draw towers
		if (control == ON)
			window->draw(frogs[0]);
			window->draw(frogs[0].getdFrogSprite());
		for (int x = 0; x < frogs.size() - 1; ++x)
		{
			window->draw(frogs[x + 1].getSightRadius());
			window->draw(frogs[x + 1]);
			window->draw(frogs[x + 1].getdFrogSprite());
		}

		// draw menu
		sidemenu.drawmenu(window, lives, eco, roundcount);

		dart.drawbutton(window);

		ninja.drawbutton(window);

		tack.drawbutton(window);

		wizard.drawbutton(window);

		window->display(); // updates the new frame 
	}

private:
	// Variables
	int lives;
	int eco;
	int numOfBloons;
	int roundcount;

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
	std::vector<Tower> dartfrogs;
	control control = ON;

	towertype towerselected;

	// Map
	sf::Texture backgroundTexture;
	sf::Sprite background;

	//Menu
	Menu sidemenu;

	//Button
	Button dart;
	Button ninja;
	Button tack;
	Button wizard;

//	Button but1;

	//Sprite
	sf::Sprite dFrogSprite;
	sf::Sprite nFrogSprite;
	sf::Sprite tFrogSprite;
	sf::Sprite wFrogSprite;
	sf::Sprite bubble;

	//Texture
	sf::Texture dartFrogTexture;
	sf::Texture ninjaFrogTexture;
	sf::Texture tackFrogTexture;
	sf::Texture wizardFrogTexture;
	sf::Texture bubbleTexture;

	// private functions
	void initVariables()
	{
		window = nullptr;
	}
	void initWindow()
	{
		videoMode.height = 525;
		videoMode.width = 950; //825

		window = new sf::RenderWindow(videoMode, "Project F");

		window->setFramerateLimit(144);

	}

	void initmenu()
	{
		sidemenu = Menu(Vector2f(825, 0), Vector2f(200, 525));

		//Heart Picture

		if (!sidemenu.getHeart().loadFromFile("Textures/Heart.png", sf::IntRect(0, 0, 80, 80)))
		{
			cout << "Image File Heart not found" << endl;
		}

		sidemenu.getSprite().setTexture(sidemenu.getHeart());

		sidemenu.getSprite().setPosition(Vector2f(15, 15));

		sidemenu.getSprite().setScale(.5, .5);

		//Money Picutre

		if (!sidemenu.getCoins().loadFromFile("Textures/Money.png", sf::IntRect(0, 0, 80, 80)))
		{
			cout << "Image File Money not found" << endl;
		}

		sidemenu.getGold().setTexture(sidemenu.getCoins());

		sidemenu.getGold().setPosition(Vector2f(105, 15));

		sidemenu.getGold().setScale(.5, .5);


		//Lives Text

		if (!sidemenu.getFont().loadFromFile("Fonts/Font.ttf"))
		{
			cout << "Font File Font not found" << endl;
		}

		sidemenu.getLivesText().setFont(sidemenu.getFont());

		sidemenu.getLivesText().setString("299");

		sidemenu.getLivesText().setCharacterSize(24);

		sidemenu.getLivesText().setFillColor(sf::Color::White);

		sidemenu.getLivesText().setPosition(Vector2f(55, 15));

		//Coin Text

		sidemenu.getMoneyeco().setFont(sidemenu.getFont());

		sidemenu.getMoneyeco().setString("499");

		sidemenu.getMoneyeco().setCharacterSize(24);

		sidemenu.getMoneyeco().setFillColor(sf::Color::White);

		sidemenu.getMoneyeco().setPosition(Vector2f(145, 15));

		//Round

		sidemenu.getRound().setFont(sidemenu.getFont());

		sidemenu.getRound().setString("Round");

		sidemenu.getRound().setCharacterSize(24);

		sidemenu.getRound().setFillColor(sf::Color::White);

		sidemenu.getRound().setPosition(Vector2f(705, 15));

		//Round Count

		sidemenu.getRoundCount().setFont(sidemenu.getFont());

		sidemenu.getRoundCount().setString("1");

		sidemenu.getRoundCount().setCharacterSize(24);

		sidemenu.getRoundCount().setFillColor(sf::Color::White);

		sidemenu.getRoundCount().setPosition(Vector2f(735, 45));

		//Menu Tower Text

		sidemenu.getMenuTowerText().setFont(sidemenu.getFont());

		sidemenu.getMenuTowerText().setString("Towers");

		sidemenu.getMenuTowerText().setCharacterSize(24);

		sidemenu.getMenuTowerText().setFillColor(sf::Color::Magenta);

		sidemenu.getMenuTowerText().setPosition(Vector2f(845, 15));
	}

	void initbutton()
	{	
		//Dart

		if (!dartFrogTexture.loadFromFile("Textures/dart.png", sf::IntRect(17, 17, 80, 80)))
		{
			cout << "Dart.png wasn't loaded" << endl;
		}

		dart.getSprite().setTexture(dartFrogTexture);

		dart.getSprite().setPosition(Vector2f(810, 55));

		dart.getSprite().setScale(1, 1);

		//Ninja

		if (!ninja.getTexture().loadFromFile("Textures/greninja.png", sf::IntRect(10, 10, 80, 80)))
		{
			cout << "Image File dart not found" << endl;
		}

		ninja.getSprite().setTexture(ninja.getTexture());

		ninja.setPosition(Vector2f(830, 150));

		ninja.getSprite().setPosition(Vector2f(820, 120));

		ninja.getSprite().setScale(1, 1);

		//Tack

		if (!tack.getTexture().loadFromFile("Textures/tack.png", sf::IntRect(10, 10, 80, 80)))
		{
			cout << "Image File dart not found" << endl;
		}

		tack.getSprite().setTexture(tack.getTexture());

		tack.setPosition(Vector2f(910, 80));

		tack.getSprite().setPosition(Vector2f(875, 55));

		tack.getSprite().setScale(1, 1);

		//Wizard

		if (!wizard.getTexture().loadFromFile("Textures/Wizard.png", sf::IntRect(10, 10, 80, 80)))
		{
			cout << "Image File dart not found" << endl;
		}

		wizard.getSprite().setTexture(wizard.getTexture());

		wizard.setPosition(Vector2f(910, 150));

		wizard.getSprite().setPosition(Vector2f(880, 120));

		wizard.getSprite().setScale(1, 1);
	}

	void initBackground()
	{
		if (!backgroundTexture.loadFromFile("Textures/MonkeyMeadow.png"))
		{
			cout << "Image File not found" << endl;
		}

		background.setTexture(backgroundTexture);

		//background.setScale(10, 10);
	}

	void initTexture()
	{
		//Dart
		
		if (!dartFrogTexture.loadFromFile("Textures/dart.png", sf::IntRect(17, 17, 80, 80)))
		{
			cout << "Dart.png wasn't loaded" << endl;
		}

		//Ninja

		if (!ninjaFrogTexture.loadFromFile("Textures/greninja.png", sf::IntRect(10, 10, 80, 80)))
		{
			cout << "Image File dart not found" << endl;
		}

		//Tack

		if (!tackFrogTexture.loadFromFile("Textures/tack.png", sf::IntRect(10, 10, 80, 80)))
		{
			cout << "Image File dart not found" << endl;
		}

		//Wizard

		if (!wizardFrogTexture.loadFromFile("Textures/Wizard.png", sf::IntRect(10, 10, 80, 80)))
		{
			cout << "Image File dart not found" << endl;
		}
	}

	void initBalloons()
	{
	
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
		Tower dart = Tower(dartFrogTexture, 3, 1, 1, 100.f);
		dart.getdFrogSprite().setPosition(Vector2f(1000, 1000));
		frogs.push_back(dart);

		Tower ninja = Tower(ninjaFrogTexture, 3, 1, 1, 100.f);
		ninja.getdFrogSprite().setPosition(Vector2f(1000, 1000));
		frogs.push_back(ninja);

		Tower tack = Tower(tackFrogTexture, 3, 1, 1, 100.f);
		tack.getdFrogSprite().setPosition(Vector2f(1000, 1000));
		frogs.push_back(tack);

		Tower wizard = Tower(wizardFrogTexture, 3, 1, 1, 100.f);
		wizard.getdFrogSprite().setPosition(Vector2f(1000, 1000));
		frogs.push_back(wizard);
	}
};