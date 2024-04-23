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
					if (eco >= 200)
					{
						Tower copyFrog = frogs[0];
						frogs.push_back(copyFrog);
						eco -= 200;
						control = OFF;
					}
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
		for (int i = 0; i < frogs.size() - 1; ++i)
		{
			frogs[i + 1].setElapsedTimeShoot(frogs[i + 1].getElapsedTimeShoot() + tempInterval);
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
				cout << "butt" << endl;
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
				cout << "butt" << endl;
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

			frogs[0].moveTower(*window, control);

			bool validBloon = true;
			float towerDegree = 0.0;

			for (int x = 0; x < frogs.size() - 1; ++x)
			{
				if (frogs[x + 1].getBloonInSight() != -1 && bloons[frogs[x + 1].getBloonInSight()]->getType() != 0
					&& frogs[x + 1].checkInRadius(bloons[frogs[x + 1].getBloonInSight()]->getPosition()))
				{
					towerDegree = frogs[x + 1].findRotateDeg(bloons[frogs[x + 1].getBloonInSight()]->getPosition());

					if (frogs[x + 1].getElapsedTimeShoot() >= frogs[x + 1].getThrowSpeed())
					{
						frogs[x + 1].shootProjectile(towerDegree);
						frogs[x + 1].getProjectiles()[frogs[x + 1].getProjectiles().size() - 1].setTexture(bubbleTexture);
						frogs[x + 1].setElapsedTimeShoot(sf::milliseconds(0));
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
						if (frogs[x + 1].getProjectiles()[i].getBloonsPopped().size() > 0)	// change for penetration difference
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
									eco++;
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
		{
			window->draw(frogs[0]);
			window->draw(frogs[0].getSightRadius());
		}
			
		for (int x = 0; x < frogs.size() - 1; ++x)
		{
			//window->draw(frogs[x + 1].getSightRadius());

			for (int i = 0; i < frogs[x + 1].getProjectiles().size(); ++i)
			{
				if (frogs[x + 1].getProjectiles()[i].isActive())
				{
					window->draw(frogs[x + 1].getProjectiles()[i]);
				}
			}
			window->draw(frogs[x + 1]);
				
		}

		window->draw(but1);

		// draw menu
		sidemenu.drawmenu(window, lives, eco);

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
		Tower frog = Tower(sf::Color::Black, sf::milliseconds(500), 1, 200.f);
		frogs.push_back(frog);
	}
};