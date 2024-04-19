#include "Balloon.hpp"

class Button : public sf::CircleShape
{
public:
	Button(const string& filename = " ")
	{
		setRadius(25.f);
		setFillColor(sf::Color::Transparent);
		setPosition(830, 80);
	}

	void drawbutton(sf::RenderWindow*& window)
	{
		window->draw(*this);

		window->draw(sprite);
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

	//Getters 
	string getfilename()
	{
		return filename;
	}

	string getdartfrog()
	{
		return dartfrog;
	}

	sf::Sprite& getSprite()
	{
		return sprite;
	}

	sf::Texture& getTexture()
	{
		return spriteTexture;
	}

	//Setters
	void setfilename(const string& file)
	{
		if (!spriteTexture.loadFromFile(file, sf::IntRect(0, 0, 80, 80)))
		{
			cout << "dartfrog File not Found" << endl;
		}
		else
		{
			sprite.setTexture(spriteTexture);

			cout << "Texture changed" << endl;
		}
	}

	void setdartfrog(const string& dart)
	{
		dartfrog = dart;
	}

private:
	//Tower 1
	sf::Sprite sprite;
	sf::Texture spriteTexture;

	int cost;

	string filename;

	string dartfrog;

	
};