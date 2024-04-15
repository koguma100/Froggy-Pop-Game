#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

using std::cout;
using std::cin;
using std::endl;
using sf::Vector2f;

enum direction
{
	UP = 1, RIGHT = 2, DOWN = 3, LEFT = 4
};

class Balloon : public sf::CircleShape
{
public:
	Balloon(int type = 1, float size = 20, const sf::Vector2f& pos = sf::Vector2f(0, 0)) : CircleShape(size) {
        switch (type)
        {
        case 1:

            color = sf::Color::Red;
            speed = 1;
            break;
        case 2:
            color = sf::Color::Blue;
            speed = 1.25;
            break;
        case 3:
            color = sf::Color::Green;
            speed = 1.50;
            break;
        default:
            color = sf::Color::Red;
            speed = 1;
        }

        this->type = type;
        direct = RIGHT;
        this->setPosition(pos);
        this->setFillColor(color);
    };

	Balloon(const Balloon& copy);

	int getType() const;

	void setType(int type);

	void moveBalloon();

private:
	int type;
	direction direct;
	sf::Color color;
	float speed;
};