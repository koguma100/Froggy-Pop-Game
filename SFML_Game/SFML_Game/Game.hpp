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
		initTextures();
		initTowers();
		initmenu();
		initbutton();
		lives = 100;
		eco = 500;
		numOfBloons = 0;
		round = 1;
		towerSelected = DART;

		elapsed_time_bloons = sf::milliseconds(0);
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
					switch (towerSelected)
					{
					case DART:
						if (eco >= dartCost)
						{
							eco -= dartCost;
							DartFrog* temp = new DartFrog(dartFrogTexture, sf::milliseconds(1000), 1, 150.f);
							temp->moveTower(*window, ON);
							frogs.push_back(temp);
							control = OFF;
						}
						break;
					case NINJA:
						if (eco >= ninjaCost)
						{
							eco -= ninjaCost;
							NinjaFrog* temp = new NinjaFrog(ninjaFrogTexture, sf::milliseconds(1500), 1, 200.f);
							temp->moveTower(*window, ON);
							frogs.push_back(temp);
							control = OFF;
						}
						break;
					case TACK:
						if (eco >= tackCost)
						{
							eco -= tackCost;
							TackFrog* temp = new TackFrog(tackFrogTexture, sf::milliseconds(2000), 2, 66.f);
							temp->moveTower(*window, ON);
							frogs.push_back(temp);
							control = OFF;
						}
						break;
					case WIZARD:
						if (eco >= wizardCost)
						{
							eco -= wizardCost;
							DartFrog* temp = new DartFrog(dartFrogTexture, sf::milliseconds(1000), 1, 150.f);
							frogs.push_back(temp);
							control = OFF;
						}
						break;
					default:
						if (eco >= dartCost)
						{
							eco -= dartCost;
							DartFrog* temp = new DartFrog(dartFrogTexture, sf::milliseconds(1000), 1, 150.f);
							temp->moveTower(*window, ON);
							frogs.push_back(temp);
							control = OFF;
						}
						break;
					}
					
				}

				if (dart.isMouseOver(*window) && ev.mouseButton.button == sf::Mouse::Left && control == OFF)
				{
					if (eco >= dartCost)
					{
						control = ON;	
					}	
					towerSelected = DART;
				}
				else if (ninja.isMouseOver(*window) && ev.mouseButton.button == sf::Mouse::Left && control == OFF)
				{
					if (eco >= ninjaCost)
					{
						control = ON;
					}
					towerSelected = NINJA;
				}
				else if (tack.isMouseOver(*window) && ev.mouseButton.button == sf::Mouse::Left && control == OFF)
				{
					if (eco >= tackCost)
					{
						control = ON;
					}
					towerSelected = TACK;
				}
				else if (wizard.isMouseOver(*window) && ev.mouseButton.button == sf::Mouse::Left && control == OFF)
				{
					if (eco >= wizardCost)
					{
						control = ON;
					}
					towerSelected = WIZARD;
				}
				if (ev.mouseButton.button == sf::Mouse::Left && control == OFF)
				{
					bool towerFound = false;
					for (int i = 4; i < frogs.size() && !towerFound; ++i)
					{
						if (frogs[i]->isMouseOver(*window))
						{
							cout << "POOP" << endl;
							currentTower = i;
							towerFound = true;
						}
					}
					if (!towerFound)
					{
						currentTower = -1;
					}
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
		
		sf::Time tempInterval = clock.restart();
		elapsed_time_bloons += tempInterval;
		for (int i = 0; i < frogs.size() - 1; ++i)
		{
			frogs[i + 1]->setElapsedTimeShoot(frogs[i + 1]->getElapsedTimeShoot() + tempInterval);
		}

		//+++++++++++++++++++++++++++++++++START OF BLOON RUSH CODE+++++++++++++++++++++++++++++++++//

		switch (round)	// round system
		{
		case 1:
			// 15 red spaced ruch
			if (bloons.size() < 15 && elapsed_time_bloons >= normal_rush_time)
			{
				spawnBalloon(1, bloons);
				elapsed_time_bloons = sf::milliseconds(0);
			}

			// 15 red bloon group rush
			if ((bloons.size() >= 15 && bloons.size() < 30) && elapsed_time_bloons >= grouped_rush_time)
			{
				spawnBalloon(1, bloons);
				elapsed_time_bloons = sf::milliseconds(0);
			}

			if ((bloons.size() >= 30 && bloons.size() < 45) && elapsed_time_bloons >= normal_rush_time)
			{
				spawnBalloon(2, bloons);
				elapsed_time_bloons = sf::milliseconds(0);
			}

			if (roundEnded(bloons) && elapsed_time_bloons > sf::milliseconds(5000))
			{
				emptyBloons(bloons);
				elapsed_time_bloons = sf::milliseconds(0);
				eco += 300;
				round++;
				cout << "Round: " << round << endl;
			}
			break;
		case 2:
			if (bloons.size() < 15 && elapsed_time_bloons >= normal_rush_time)
			{
				spawnBalloon(2, bloons);
				elapsed_time_bloons = sf::milliseconds(0);
			}

			// 15 red bloon group rush
			if ((bloons.size() >= 15 && bloons.size() < 30) && elapsed_time_bloons >= grouped_rush_time)
			{
				spawnBalloon(2, bloons);
				elapsed_time_bloons = sf::milliseconds(0);
			}

			if ((bloons.size() >= 30 && bloons.size() < 45) && elapsed_time_bloons >= normal_rush_time)
			{
				spawnBalloon(3, bloons);
				elapsed_time_bloons = sf::milliseconds(0);
			}

			if (roundEnded(bloons) && elapsed_time_bloons > sf::milliseconds(5000))
			{
				emptyBloons(bloons);
				elapsed_time_bloons = sf::milliseconds(0);
				eco += 400;
				round++;
				cout << "Round: " << round << endl;
			}
			break;
		case 3:
			if (bloons.size() < 15 && elapsed_time_bloons >= grouped_rush_time)
			{
				spawnBalloon(2, bloons);
				elapsed_time_bloons = sf::milliseconds(0);
			}

			// 15 red bloon group rush
			if ((bloons.size() >= 15 && bloons.size() < 30) && elapsed_time_bloons >= grouped_rush_time)
			{
				spawnBalloon(3, bloons);
				elapsed_time_bloons = sf::milliseconds(0);
			}

			if ((bloons.size() >= 30 && bloons.size() < 45) && elapsed_time_bloons >= normal_rush_time)
			{
				spawnBalloon(4, bloons);
				elapsed_time_bloons = sf::milliseconds(0);
			}
			if ((bloons.size() >= 45 && bloons.size() < 60) && elapsed_time_bloons >= normal_rush_time)
			{
				spawnBalloon(3, bloons);
				elapsed_time_bloons = sf::milliseconds(0);
			}

			if (roundEnded(bloons) && elapsed_time_bloons > sf::milliseconds(5000))
			{
				emptyBloons(bloons);
				elapsed_time_bloons = sf::milliseconds(0);
				eco += 400;
				round++;
				cout << "Round: " << round << endl;
			}
			break;
		}

		//+++++++++++++++++++++++++++++++++END OF BLOON RUSH CODE+++++++++++++++++++++++++++++++++//
		
		// frog updates
		// track mouse
		if (!roundEnded(bloons))
		{
			balloonMovement();

			switch (towerSelected)
			{
			case DART:
				dartFrog.moveTower(*window, control);
				break;
			case NINJA:
				ninjaFrog.moveTower(*window, control);
				break;
			case TACK:
				tackFrog.moveTower(*window, control);
				break;
			case WIZARD:
				frogs[3]->moveTower(*window, control);
				break;
			default:
				dartFrog.moveTower(*window, control);
				break;
			}

			bool validBloon = true;
			float towerDegree = 0.0;

			for (int x = 0; x < frogs.size() - 4; ++x)
			{
				frogs[x + 4]->shoot(bloons, bubbleTexture, towerDegree);

				for (int i = 0; i < frogs[x + 4]->getProjectiles().size(); ++i)
				{
					if (!(frogs[x + 4]->getProjectiles()[i].getGlobalBounds().intersects(frogs[x + 4]->getSightRadius().getGlobalBounds())))
					{
						frogs[x + 4]->getProjectiles()[i].setActive(false);
					}
					else
					{
						if (frogs[x + 4]->getProjectiles()[i].isActive())
						{
							for (int bloonIndex = 0; bloonIndex < bloons.size(); ++bloonIndex)
							{
								if (frogs[x + 4]->getProjectiles()[i].getBloonsPopped().size() >= frogs[x + 4]->getPierce())	// change for penetration difference
								{
									frogs[x + 4]->getProjectiles()[i].setActive(false);
								}
								else
								{
									if (frogs[x + 4]->getProjectiles()[i].getGlobalBounds().intersects(bloons[bloonIndex]->getGlobalBounds()))
									{
										validBloon = true;

										for (int k = 0; k < frogs[x + 4]->getProjectiles()[i].getBloonsPopped().size(); k++)
										{
											if (frogs[x + 4]->getProjectiles()[i].getBloonsPopped()[k] == bloonIndex)
											{
												validBloon = false;
											}
										}
										if (validBloon)
										{
											bloons[bloonIndex]->bloonPop();
											eco++;
											frogs[x + 4]->getProjectiles()[i].bloonHit(bloonIndex);
										}
									}
								}

							}
						}
					}
					
					frogs[x + 4]->getProjectiles()[i].move_bubble();
				}
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

		// draw menu
		sidemenu.drawmenu(window, lives, eco, round);

		dart.drawbutton(window);

		ninja.drawbutton(window);

		tack.drawbutton(window);

		wizard.drawbutton(window);

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
		{
			switch (towerSelected)
			{
			case DART:
				window->draw(dartFrog);
				window->draw(dartFrog.getSightRadius());
				window->draw(dartFrog.getdFrogSprite());
				break;
			case NINJA:
				window->draw(ninjaFrog);
				window->draw(ninjaFrog.getSightRadius());
				window->draw(ninjaFrog.getdFrogSprite());
				break;
			case TACK:
				window->draw(tackFrog);
				window->draw(tackFrog.getSightRadius());
				window->draw(tackFrog.getdFrogSprite());
				break;
			case WIZARD:
				window->draw(*frogs[3]);
				window->draw(frogs[3]->getSightRadius());
				window->draw(frogs[3]->getdFrogSprite());
				break;
			}
		}
			
		for (int x = 0; x < frogs.size() - 4; ++x)
		{
			//window->draw(frogs[x + 4].getSightRadius());
			if (x + 4 == currentTower)
			{
				window->draw(frogs[x + 4]->getSightRadius());
			}
			for (int i = 0; i < frogs[x + 4]->getProjectiles().size(); ++i)
			{
				if (frogs[x + 4]->getProjectiles()[i].isActive())
				{
					window->draw(frogs[x + 4]->getProjectiles()[i]);
				}
			}
			window->draw(*frogs[x + 4]);	
			window->draw(frogs[x + 4]->getdFrogSprite());
		}

		if (lives <= 0)
		{
			sf::RectangleShape black = sf::RectangleShape(Vector2f(1600, 340));
			black.setFillColor(sf::Color::Black);
			black.setPosition(100, 300);
			window->draw(black);
			window->draw(gameOverMessage);
		}

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
	sf::Time elapsed_time_bloons;

	// Game Objects
	vector<Balloon*> bloons;
	
	sf::Texture bubbleTexture;

	// Game Over Text
	sf::Text gameOverMessage;

	// Checkpoints
	vector<Checkpoint> checkpoints;

	// Towers
	std::vector<Tower*> frogs;

	DartFrog dartFrog;
	NinjaFrog ninjaFrog;
	TackFrog tackFrog;

	sf::Texture dartFrogTexture;
	sf::Texture ninjaFrogTexture;
	sf::Texture tackFrogTexture;
	sf::Texture wizardFrogTexture;
	int dartCost = 200,
		ninjaCost = 350,
		tackCost = 250,
		wizardCost = 450,
	    currentTower = -1;

	towertype towerSelected;

	// Buttons
	control control = OFF;

	Button but1;
	Button dart;
	Button ninja;
	Button tack;
	Button wizard;

	// Map
	sf::Texture backgroundTexture;
	sf::Sprite background;

	//Menu
	Menu sidemenu;

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

	void initmenu()
	{
		sidemenu = Menu(Vector2f(1525, 0), Vector2f(375, 900));

		//Heart Picture

		if (!sidemenu.getHeart().loadFromFile("Textures/Heart.png", sf::IntRect(0, 0, 80, 80)))
		{
			cout << "Image File Heart not found" << endl;
		}

		sidemenu.getSprite().setTexture(sidemenu.getHeart());

		sidemenu.getSprite().setPosition(Vector2f(15, 15));

		sidemenu.getSprite().setScale(1, 1);

		//Money Picutre

		if (!sidemenu.getCoins().loadFromFile("Textures/Money.png", sf::IntRect(0, 0, 80, 80)))
		{
			cout << "Image File Money not found" << endl;
		}

		sidemenu.getGold().setTexture(sidemenu.getCoins());

		sidemenu.getGold().setPosition(Vector2f(165, 15));

		sidemenu.getGold().setScale(1, 1);


		//Lives Text

		if (!sidemenu.getFont().loadFromFile("Fonts/Font.ttf"))
		{
			cout << "Font File Font not found" << endl;
		}

		sidemenu.getLivesText().setFont(sidemenu.getFont());

		sidemenu.getLivesText().setString("299");

		sidemenu.getLivesText().setCharacterSize(36);

		sidemenu.getLivesText().setFillColor(sf::Color::White);

		sidemenu.getLivesText().setPosition(Vector2f(100, 25));

		//Coin Text

		sidemenu.getMoneyeco().setFont(sidemenu.getFont());

		sidemenu.getMoneyeco().setString("499");

		sidemenu.getMoneyeco().setCharacterSize(36);

		sidemenu.getMoneyeco().setFillColor(sf::Color::White);

		sidemenu.getMoneyeco().setPosition(Vector2f(260, 25));

		//Tower Text

		sidemenu.getTowerlogo().setFont(sidemenu.getFont());

		sidemenu.getTowerlogo().setString("Towers");

		sidemenu.getTowerlogo().setCharacterSize(64);

		sidemenu.getTowerlogo().setFillColor(sf::Color::Magenta);

		sidemenu.getTowerlogo().setPosition(Vector2f(1555, 15));

		//Round

		sidemenu.getRound().setFont(sidemenu.getFont());

		sidemenu.getRound().setString("Round");

		sidemenu.getRound().setCharacterSize(48);

		sidemenu.getRound().setFillColor(sf::Color::White);

		sidemenu.getRound().setPosition(Vector2f(1300, 25));

		//Round Count

		sidemenu.getRoundCount().setFont(sidemenu.getFont());

		sidemenu.getRoundCount().setString("1");

		sidemenu.getRoundCount().setCharacterSize(36);

		sidemenu.getRoundCount().setFillColor(sf::Color::White);

		sidemenu.getRoundCount().setPosition(Vector2f(1360, 100));

		//Dart name

		sidemenu.getDartName().setFont(sidemenu.getFont());

		sidemenu.getDartName().setString("Dart Frog");

		sidemenu.getDartName().setCharacterSize(24);

		sidemenu.getDartName().setFillColor(sf::Color::Green);

		sidemenu.getDartName().setPosition(Vector2f(1540, 110));

		//Dart Cost

		sidemenu.getDartCost().setFont(sidemenu.getFont());

		sidemenu.getDartCost().setString("200");

		sidemenu.getDartCost().setCharacterSize(24);

		sidemenu.getDartCost().setFillColor(sf::Color::Green);

		sidemenu.getDartCost().setPosition(Vector2f(1570, 300));

		//Ninja Name

		sidemenu.getNinjaName().setFont(sidemenu.getFont());

		sidemenu.getNinjaName().setString("Ninja Frog");

		sidemenu.getNinjaName().setCharacterSize(24);

		sidemenu.getNinjaName().setFillColor(sf::Color::Green);

		sidemenu.getNinjaName().setPosition(Vector2f(1540, 345));

		//Ninja Cost

		sidemenu.getNinjaCost().setFont(sidemenu.getFont());

		sidemenu.getNinjaCost().setString("350");

		sidemenu.getNinjaCost().setCharacterSize(24);

		sidemenu.getNinjaCost().setFillColor(sf::Color::Green);

		sidemenu.getNinjaCost().setPosition(Vector2f(1573, 530));

		//Tack Name

		sidemenu.getTackName().setFont(sidemenu.getFont());

		sidemenu.getTackName().setString("Frog Army");

		sidemenu.getTackName().setCharacterSize(24);

		sidemenu.getTackName().setFillColor(sf::Color::Green);

		sidemenu.getTackName().setPosition(Vector2f(1680, 110));

		//Tack Cost

		sidemenu.getTackCost().setFont(sidemenu.getFont());

		sidemenu.getTackCost().setString("250");

		sidemenu.getTackCost().setCharacterSize(24);

		sidemenu.getTackCost().setFillColor(sf::Color::Green);

		sidemenu.getTackCost().setPosition(Vector2f(1710, 300));

		//Wizard Name

		sidemenu.getWizardName().setFont(sidemenu.getFont());

		sidemenu.getWizardName().setString("Wizard Frog");

		sidemenu.getWizardName().setCharacterSize(24);

		sidemenu.getWizardName().setFillColor(sf::Color::Green);

		sidemenu.getWizardName().setPosition(Vector2f(1660, 345));

		//Wizard Cost

		sidemenu.getWizardCost().setFont(sidemenu.getFont());

		sidemenu.getWizardCost().setString("450");

		sidemenu.getWizardCost().setCharacterSize(24);

		sidemenu.getWizardCost().setFillColor(sf::Color::Green);

		sidemenu.getWizardCost().setPosition(Vector2f(1710, 530));
	}



	void initbutton()
	{
		//Dart

		if (!dartFrogTexture.loadFromFile("Textures/dart.png", sf::IntRect(120, 210, 1800, 1710)))
		{
			cout << "Dart.png wasn't loaded" << endl;
		}

		dart.getSprite().setTexture(dartFrogTexture);

		dart.setPosition(Vector2f(1545, 180));
		dart.getSprite().setPosition(dart.getPosition());

		dart.getSprite().setScale(.06, .06);

		//Ninja

		if (!ninja.getTexture().loadFromFile("Textures/greninja.png", sf::IntRect(120, 210, 1800, 1710)))
		{
			cout << "Image File dart not found" << endl;
		}

		ninja.getSprite().setTexture(ninja.getTexture());

		ninja.setPosition(Vector2f(1545, 395));

		ninja.getSprite().setPosition(ninja.getPosition());

		ninja.getSprite().setScale(.06, .06);

		//Tack

		if (!tack.getTexture().loadFromFile("Textures/tack.png", sf::IntRect(0, 0, 1920, 1920)))
		{
			cout << "Image File dart not found" << endl;
		}

		tack.getSprite().setTexture(tack.getTexture());

		tack.setPosition(Vector2f(1680, 180));

		tack.getSprite().setPosition(Vector2f(tack.getPosition()));

		tack.getSprite().setScale(0.055, 0.055);

		//Wizard

		if (!wizard.getTexture().loadFromFile("Textures/Wizard.png", sf::IntRect(120, 210, 1800, 1710)))
		{
			cout << "Image File dart not found" << endl;
		}

		wizard.getSprite().setTexture(wizard.getTexture());

		wizard.setPosition(Vector2f(1680, 395));

		wizard.getSprite().setPosition(wizard.getPosition());

		wizard.getSprite().setScale(.06, .06);
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

	void initTextures()		// includes game over message init
	{
		// Dart
		if (!dartFrogTexture.loadFromFile("Textures/dart.png", sf::IntRect(120, 210, 1800, 1710)))
		{
			cout << "Dart.png wasn't loaded" << endl;
		}

		// Ninja
		if (!ninjaFrogTexture.loadFromFile("Textures/greninja.png", sf::IntRect(120, 210, 1800, 1710)))
		{
			cout << "Image File dart not found" << endl;
		}

		// Tack
		if (!tackFrogTexture.loadFromFile("Textures/tack.png", sf::IntRect(0, 0, 1920, 1920)))
		{
			cout << "Image File dart not found" << endl;
		}

		// Wizard
		if (!wizardFrogTexture.loadFromFile("Textures/Wizard.png", sf::IntRect(120, 210, 1800, 1710)))
		{
			cout << "Image File dart not found" << endl;
		}

		if (!bubbleTexture.loadFromFile("Textures/bubble.png"))
		{
			cout << "Bubble.png file not found" << endl;
		}

		gameOverMessage.setFont(sidemenu.getFont());
		gameOverMessage.setFillColor(sf::Color::Red);
		gameOverMessage.setCharacterSize(256);
		gameOverMessage.setPosition(200, 300);
		gameOverMessage.setStyle(sf::Text::Bold);
		gameOverMessage.setString("Game Over!");

	}

	void initTowers()
	{
		dartFrog = DartFrog(dartFrogTexture, sf::milliseconds(1000), 1, 150.f);
		dartFrog.getdFrogSprite().setPosition(Vector2f(1000, 1000));
		frogs.push_back(&dartFrog);

		ninjaFrog = NinjaFrog(ninjaFrogTexture, sf::milliseconds(1500), 1, 200.f);
		ninjaFrog.getdFrogSprite().setPosition(Vector2f(1000, 1000));
		frogs.push_back(&ninjaFrog);
		tackFrog = TackFrog(tackFrogTexture, sf::milliseconds(1000), 1, 66.f);
		tackFrog.getdFrogSprite().setPosition(Vector2f(1000, 1000));
		frogs.push_back(&tackFrog);

		DartFrog wizard = DartFrog(wizardFrogTexture, sf::milliseconds(1000), 1, 100.f);
		wizard.getdFrogSprite().setPosition(Vector2f(1000, 1000));
		frogs.push_back(&wizard);
	}
};