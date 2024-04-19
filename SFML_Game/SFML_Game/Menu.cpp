#include "Menu.hpp"

sf::Texture& Menu::getHeart()
{
	return heart;
}

sf::Sprite& Menu::getSprite()
{
	return lives;
}

sf::Texture& Menu::getCoins()
{
	return coins;
}

sf::Sprite& Menu::getGold()
{
	return gold;
}

sf::Font& Menu::getFont()
{
	return font;
}

sf::Text& Menu::getLivesText()
{
	return livestext;
}

sf::Text& Menu::getMoneyeco()
{
	return Moneyeco;
}

sf::Text& Menu::getRound()
{
	return Round;
}

sf::Text& Menu::getRoundCount()
{
	return RoundCount;
}

sf::Text& Menu::getMenuTowerText()
{
	return MenuTowerText;
}

void Menu::drawmenu(sf::RenderWindow*& window, int& livesint, int& casheco, int& RdCount)
{
	window->draw(*this);

	window->draw(lives);

	window->draw(gold);

	livestext.setString(std::to_string(livesint));

	window->draw(livestext);

	Moneyeco.setString(std::to_string(casheco));

	window->draw(Moneyeco);

	window->draw(Round);

	RoundCount.setString(std::to_string(RdCount));

	window->draw(RoundCount);

	window->draw(MenuTowerText);

}
