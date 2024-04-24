#include "TackFrog.hpp"

class Menu : public sf::RectangleShape
{
public:
	Menu(const Vector2f& pos = Vector2f(0,0), const Vector2f& size = Vector2f(0, 0)) : RectangleShape(size)
	{
		this->setPosition(pos);

		this->setFillColor(sf::Color::Yellow);

	}

	Menu(const Menu& copy)
	{
		this->setPosition(copy.getPosition());

		this->setFillColor(copy.getFillColor());

		this->setSize(copy.getSize());
	}

	~Menu()
	{

	}

	//Getters
	sf::Texture& getHeart();

	sf::Sprite& getSprite();

	sf::Texture& getCoins();

	sf::Sprite& getGold();

	sf::Font& getFont();

	sf::Text& getLivesText();

	sf::Text& getMoneyeco();

	void drawmenu(sf::RenderWindow*& window, int& livesint, int& casheco); 

 private:

	 //Heart
	 sf::Texture heart;
	 sf::Sprite lives;

	 //Money
	 sf::Texture coins;
	 sf::Sprite gold;

	 //Font
	 sf::Font font;
	 sf::Text livestext;
	 sf::Text Moneyeco;

};
