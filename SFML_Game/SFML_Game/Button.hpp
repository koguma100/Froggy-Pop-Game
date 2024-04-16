#include "Balloon.hpp"

class Button : public sf::CircleShape
{
public:
	Button()
	{
		setRadius(25.f);
		setFillColor(sf::Color::Blue);
		setPosition(500, 0);
	}
};