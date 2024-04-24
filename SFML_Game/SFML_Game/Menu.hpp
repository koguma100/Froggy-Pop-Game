
#include "Tower.hpp"

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

	sf::Text& getTowerlogo();

	sf::Text& getRound();

	sf::Text& getRoundCount();

	sf::Text& getDartName();

	sf::Text& getNinjaName();

	sf::Text& getTackName();

	sf::Text& getWizardName();

	sf::Text& getDartCost();

	sf::Text& getNinjaCost();

	sf::Text& getTackCost();

	sf::Text& getWizardCost();

	void drawmenu(sf::RenderWindow*& window, int& livesint, int& casheco, int& RdCount); 

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
	 sf::Text Towerlogo;
	 sf::Text Round;
	 sf::Text RoundCount;
	 sf::Text DartName;
	 sf::Text NinjaName;
	 sf::Text TackName;
	 sf::Text WizardName;
	 sf::Text DartCost;
	 sf::Text NinjaCost;
	 sf::Text TackCost;
	 sf::Text WizardCost;
};
