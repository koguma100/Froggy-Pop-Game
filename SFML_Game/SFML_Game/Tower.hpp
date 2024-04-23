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
	Tower(const sf::Texture& texture, sf::Time newThrowSpeed, int newThrowAmount,
		float newSightRadius)
	{
		dFrogTexture = texture;
		dFrog.setTexture(texture);
		throwSpeed = newThrowSpeed;
		throwAmount = newThrowAmount;
		shooting = false;
		bloonInSight = -1;
		elapsedTimeShoot = sf::milliseconds(0);
		sightRadius.setRadius(newSightRadius);
		sightRadius.setFillColor(sf::Color::Transparent);
		sightRadius.setOutlineColor(sf::Color::Blue);
		sightRadius.setOutlineThickness(3.f);
		this->setSize(sf::Vector2f(50.f, 50.f));
		this->setFillColor(sf::Color::Transparent);
		this->setOutlineColor(sf::Color::Transparent);
		this->setOutlineThickness(1.f);
		this->setOrigin(getSize().x * .5f, getSize().y * .5f);
		sightRadius.setOrigin(sightRadius.getRadius(), sightRadius.getRadius());
		dFrog.setOrigin(dFrog.getTexture()->getSize().x * .5f, dFrog.getTexture()->getSize().y * .5f);
	}
	Tower()
	{
		this->setSize(sf::Vector2f(50.f, 50.f));
		sightRadius.setRadius(50.f);
		sightRadius.setFillColor(sf::Color::White);
		sightRadius.setOrigin(sightRadius.getRadius(), sightRadius.getRadius());
	}
	~Tower()
	{
	}

	// getters
	sf::Time getThrowSpeed()
	{
		return throwSpeed;
	}
	int getThrowAmount()
	{
		return throwAmount;
	}
	int getBloonInSight()
	{
		return bloonInSight;
	}
	sf::CircleShape getSightRadius()
	{
		return sightRadius;
	}

	sf::Sprite& getdFrogSprite()
	{
		return dFrog;
	}

	sf::Texture& getdFrogTexture()
	{
		return dFrogTexture;
	}

	bool getShooting()
	{
		return shooting;
	}

	sf::Time getElapsedTimeShoot()
	{
		return elapsedTimeShoot;
	}

	vector<Bubble>& getProjectiles()
	{
		return projectiles;
	}

	// Setters

	void setThrowSpeed(sf::Time newThrowSpeed)
	{
		throwSpeed = newThrowSpeed;
	}
	void setThrowAmount(int newThrowAmount)
	{
		throwAmount = newThrowAmount;
	}
	void setBloonInSight(int bloonIndex)
	{
		bloonInSight = bloonIndex;
	}
	void setSightRadius(sf::CircleShape newSightRadius)
	{
		sightRadius = newSightRadius;
	}

	void setShooting(bool mode)
	{
		shooting = true;
	}

	void setElapsedTimeShoot(sf::Time time)
	{
		elapsedTimeShoot = time;
	}

	// Real Functions
	void moveTower(sf::RenderWindow& window, control control) // links the tower with the current mouse position
	{
		if (control == ON)
		{
			this->setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			sightRadius.setPosition(this->getPosition());
			dFrog.setPosition(getPosition());
		}
		else
		{
			setPosition(Vector2f(2000, 110));
			dFrog.setPosition(getPosition());
		}
	}

	float findRotateDeg(sf::Vector2f coordinates)
	{
		float tpx = (this->getPosition().x - coordinates.x);
		float tpy = (this->getPosition().y - coordinates.y);

		float rotateRad = atan2(tpx, -tpy);

		float rotateDeg = rotateRad * (180 / PI);

		this->setRotation(rotateDeg);

		this->dFrog.setRotation(rotateDeg);

		return rotateDeg;
	}

	bool checkInRadius(sf::Vector2f coordinates)
	{
		float posBalX = coordinates.x;
		float posBalY = coordinates.y;

		float posCirX = sightRadius.getPosition().x;
		float posCirY = sightRadius.getPosition().y;

		float xDisplacement = posBalX - posCirX;
		float yDisplacement = posBalY - posCirY;

		float hypotenuse = pow(xDisplacement, 2) + pow(yDisplacement, 2);
		hypotenuse = sqrt(hypotenuse);

		if (hypotenuse < sightRadius.getRadius())
		{
			return true;
		}
		return false;
	}

	void shootProjectile(float degrees)
	{
		Bubble temp = Bubble(sf::Vector2f(getPosition().x - 20, getPosition().y - 20), degrees);
		projectiles.push_back(temp);
	}

private:

	sf::Time throwSpeed;
	sf::Time elapsedTimeShoot;
	int throwAmount;
	int bloonInSight;
	bool shooting;
	sf::CircleShape sightRadius;
	vector<Bubble> projectiles;
	sf::Sprite dFrog;
	sf::Texture dFrogTexture;
};
