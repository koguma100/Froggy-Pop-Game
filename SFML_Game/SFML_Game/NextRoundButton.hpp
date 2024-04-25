#include "Balloon.hpp"

class NextRoundButton : public sf::RectangleShape
{
public:
	NextRoundButton()
	{
		setSize(Vector2f(233.f, 273.f));
		setFillColor(sf::Color(227, 129, 129, 1000));
		setOutlineColor(sf::Color::Black);
		setOutlineThickness(3.f);
		setPosition(Vector2f(1547, 600));
	}

	void drawbutton(sf::RenderWindow*& window)
	{
		window->draw(*this);
	}

	bool isMouseOver(sf::RenderWindow& window) // checks to see if the mouse is over the button
	{
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float butPosX = this->getPosition().x;
		float butPosY = this->getPosition().y;

		float butPosWidthX = this->getPosition().x + this->getLocalBounds().width;
		float butPosHeightY = this->getPosition().y + this->getLocalBounds().height;

		if (mouseX < butPosWidthX && mouseX > butPosX && mouseY < butPosHeightY && mouseY > butPosY)
		{
			return true;
		}
		return false;
	}
};