#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using sf::Vector2f;

enum direction
{
	UP = 1, RIGHT = 2, DOWN = 3, LEFT = 4
};

class Checkpoint : public sf::RectangleShape
{
public:
	Checkpoint(direction newDirection, const Vector2f& size, const Vector2f& pos) : RectangleShape(size)
	{
		direct = newDirection;
		setPosition(pos);
		setFillColor(sf::Color::Transparent);
	}
	
	direction getDirection() const
	{
		return direct;
	}
private:
	direction direct;
};
