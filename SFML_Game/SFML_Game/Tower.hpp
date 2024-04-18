#include "Button.hpp"

#define PI 3.14153965
#define WINDOWHEIGHT 525
#define WINDOWWIDTH 825

enum control
{
	ON = 1, OFF = 0
};

class Tower : public sf::RectangleShape
{
public:
	Tower(sf::Color newSprite, /*Projectile*/ int newProjectile, double newThrowSpeed, int newThrowAmount, 
		float newSightRadius)
	{
		sprite = newSprite;
		//projectile = newProjectile;
		throwSpeed = newThrowSpeed;
		throwAmount = newThrowAmount;
		sightRadius.setRadius(newSightRadius);
		sightRadius.setFillColor(sf::Color::White);
		this->setSize(sf::Vector2f(50.f, 50.f));
		this->setFillColor(sf::Color::Black);
		this->setOutlineColor(sf::Color::Black);
		this->setOutlineThickness(1.f);
		this->setOrigin(getSize().x * .5f, getSize().y * .5f);
		sightRadius.setOrigin(this->getOrigin().x + 25.f, this->getOrigin().y + 25.f);
	}
	Tower()
	{
		sprite = sf::Color::Black;
		this->setSize(sf::Vector2f(50.f, 50.f));
		sightRadius.setRadius(50.f);
		sightRadius.setFillColor(sf::Color::White);
		sightRadius.setOrigin(this->getOrigin().x + 25.f, this->getOrigin().y + 25.f);
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
	sf::CircleShape getSightRadius()
	{
		return sightRadius;
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
	void setSightRadius(sf::CircleShape newSightRadius)
	{
		sightRadius = newSightRadius;
	}


	// Real Functions
	void moveTower(sf::RenderWindow& window, control control) // links the tower with the current mouse position
	{
		if (control == ON)
		{
			this->setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			sightRadius.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		}
	}

	void trackMouse(sf::RenderWindow &window, sf::Vector2f coordinates)
	{
		float tpx = (this->getPosition().x - coordinates.x);
		float tpy = (this->getPosition().y - coordinates.y);

		float rotateRad = atan2(tpx, -tpy);

		float rotateDeg = rotateRad * (180 / PI);

		this->setRotation(rotateDeg);
	}

private:
	sf::Color sprite;
	//Projectile projectile
	double throwSpeed;
	int throwAmount;
	sf::CircleShape sightRadius;
};