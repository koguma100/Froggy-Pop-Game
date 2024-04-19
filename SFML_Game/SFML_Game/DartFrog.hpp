#include "Tower.hpp"

class DartFrog : public Tower
{
public:

	DartFrog(const sf::Color& color = sf::Color::Red, double throwSpeed = 1.0, int throwAmount = 1, double sightRadius = 30)
		: Tower(color, throwSpeed, throwAmount, sightRadius)
	{

	}

	void shoot()
	{
		Bubble* temp = new Bubble(getPosition());
		bubbles.push_back(temp);
	}

private:
	vector<Bubble*> bubbles;
};