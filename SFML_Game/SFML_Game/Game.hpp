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
		initmenu();
		initTextures();
		lives = 100;
		eco = 500;
		numOfBloons = 0;
		round = 1;
		elapsed_time_bloons = clock.getElapsedTime();
		elapsed_time_shoot = elapsed_time_bloons;
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
		
		sf::Time tempInterval = clock.restart();
		elapsed_time_bloons += tempInterval;
		elapsed_time_shoot += tempInterval;

		//+++++++++++++++++++++++++++++++++START OF BLOON RUSH CODE+++++++++++++++++++++++++++++++++//

		if (round == 1)	// will probably make a round function to make update less cluttered
		{
			// 15 red spaced ruch
			if (numOfBloons < 15 && elapsed_time_bloons >= normal_rush_time)
			{
				spawnBalloon(1, bloons);
				numOfBloons++;
				elapsed_time_bloons = sf::milliseconds(0);
			}

			// 15 red bloon group rush
			if ((numOfBloons >= 15 && numOfBloons < 30) && elapsed_time_bloons >= grouped_rush_time)
			{
				spawnBalloon(1, bloons);
				numOfBloons++;
				elapsed_time_bloons = sf::milliseconds(0);
			}

			if ((numOfBloons >= 30 && numOfBloons < 45) && elapsed_time_bloons >= normal_rush_time)
			{
				spawnBalloon(2, bloons);
				numOfBloons++;
				elapsed_time_bloons = sf::milliseconds(0);
			}
		}

		balloonMovement();

		//+++++++++++++++++++++++++++++++++END OF BLOON RUSH CODE+++++++++++++++++++++++++++++++++//
		
		// frog updates
		// track mouse
		frogs[0].moveTower(*window, control);

		bool validBloon = true;
		float towerDegree = 0.0;

		if (roundEnded(bloons))
		{
			emptyBloons(bloons);
		}
		else
		{
			for (int x = 0; x < frogs.size() - 1; ++x)
			{
				if (frogs[x + 1].getBloonInSight() != -1 && bloons[frogs[x + 1].getBloonInSight()]->getType() != 0
					&& frogs[x + 1].checkInRadius(bloons[frogs[x + 1].getBloonInSight()]->getPosition()))
				{
					towerDegree = frogs[x + 1].findRotateDeg(bloons[frogs[x + 1].getBloonInSight()]->getPosition());

					if (elapsed_time_shoot >= frogs[x + 1].getThrowSpeed())
					{
						frogs[x + 1].shootProjectile(towerDegree);
						frogs[x + 1].getProjectiles()[frogs[x + 1].getProjectiles().size() - 1].setTexture(bubbleTexture);
						elapsed_time_shoot = sf::milliseconds(0);
					}
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
				/*if (bloons.size() > 0 && frogs[x + 1].checkInRadius(bloons[0]->getPosition()))
				{
					frogs[x + 1].findRotateDeg(bloons[0]->getPosition());
				}*/

				for (int i = 0; i < frogs[x + 1].getProjectiles().size(); ++i)
				{
					for (int bloonIndex = 0; bloonIndex < bloons.size(); ++bloonIndex)
					{
						if (frogs[x + 1].getProjectiles()[i].getBloonsPopped().size() > 0)
						{
							frogs[x + 1].getProjectiles()[i].setActive(false);
						}
						else
						{
							if (frogs[x + 1].getProjectiles()[i].getGlobalBounds().intersects(bloons[bloonIndex]->getGlobalBounds()))
							{
								validBloon = true;

								for (int k = 0; k < frogs[x + 1].getProjectiles()[i].getBloonsPopped().size(); k++)
								{
									if (frogs[x + 1].getProjectiles()[i].getBloonsPopped()[k] == bloonIndex)
									{
										validBloon = false;
									}
								}
								if (validBloon)
								{
									bloons[bloonIndex]->bloonPop();
									frogs[x + 1].getProjectiles()[i].bloonHit(bloonIndex);
								}
							}
						}
						
					}
					frogs[x + 1].getProjectiles()[i].move_bubble();
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
			
			for (int i = 0; i < frogs[x + 1].getProjectiles().size(); ++i)
			{
				if (frogs[x + 1].getProjectiles()[i].isActive())
				{
					window->draw(frogs[x + 1].getProjectiles()[i]);
				}
			}
			
		}

		window->draw(but1);

		// draw menu
		sidemenu.drawmenu(window, lives, eco);

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
	sf::Time elapsed_time_shoot;

	// Game Objects
	vector<Balloon*> bloons;
	sf::Texture bubbleTexture;

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
	Menu sidemenu;

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

	void initTextures()
	{
		if (!bubbleTexture.loadFromFile("Textures/bubble.png"))
		{
			cout << "Bubble.png file not found" << endl;
		}
	}

	void initTowers()
	{
		Tower frog = Tower(sf::Color::Black, sf::milliseconds(300), 1, 100.f);
		frogs.push_back(frog);
	}
};