#include "Tower.hpp"

class DartFrog : public Tower
{
	DartFrog(const sf::Texture& texture, sf::Time newThrowSpeed, int newThrowAmount,
		float newSightRadius) : Tower(texture, newThrowSpeed, newThrowAmount, newSightRadius)
	{
		
	}

	virtual void shootProjectile(float degrees)
	{

	}

};