#include "Button.hpp"

enum control
{
	ON = 1, OFF = 0
};

class Tower : public sf::RectangleShape
{
public:
	Tower(sf::Color newSprite, /*Projectile*/ int newProjectile, double newThrowSpeed, int newThrowAmount)
	{
		sprite = newSprite;
		//projectile = newProjectile;
		throwSpeed = newThrowSpeed;
		throwAmount = newThrowAmount;
		this->setSize(sf::Vector2f(50.f, 50.f));
		this->setFillColor(sf::Color::Black);
		this->setOutlineColor(sf::Color::Black);
		this->setOutlineThickness(1.f);
	}
	Tower()
	{
		sprite = sf::Color::Black;
		this->setSize(sf::Vector2f(50.f, 50.f));
	}
	~Tower()
	{
	}

	// getters
	sf::Color getSprite()
	{
		return sprite;
	}
	//Projectile getProjectile()
	//{
	//	return projectile;
	//}
	double getThrowSpeed()
	{
		return throwSpeed;
	}
	int getThrowAmount()
	{
		return throwAmount;
	}

	// Setters
	void setSprite(sf::Color newSprite)
	{
		sprite = newSprite;
	}
	//void setProjectile(Projectile newProjectile)
	//{
	//	projectile = newProjectile;
	//}
	void setThrowSpeed(double newThrowSpeed)
	{
		throwSpeed = newThrowSpeed;
	}
	void setThrowAmount(int newThrowAmount)
	{
		throwAmount = newThrowAmount;
	}


	// Real Functions
	void moveTower(sf::RenderWindow* window, control control) // links the tower with the current mouse position
	{
		if (control == ON)
			this->setPosition(sf::Mouse::getPosition(*window).x - 25.f, sf::Mouse::getPosition(*window).y - 25.f);
	}

private:
	sf::Color sprite;
	//Projectile projectile
	double throwSpeed;
	int throwAmount;
};