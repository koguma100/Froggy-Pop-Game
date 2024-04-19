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
	
private:
	sf::Sprite sprite;
	sf::Texture spriteTexture;
	int cost;
	string fileName;
};