#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
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

class Button : public sf::RectangleShape
{
public:
	Button(const Vector2f& pos = Vector2f(0, 0), const Vector2f& size = Vector2f(20, 20), 
		const sf::Color& color = sf::Color::Green) : RectangleShape(size)
	{
		setPosition(pos);
		setFillColor(color);
		mode = true;
	}

	Button(const Button& copy)
	{
		setPosition(copy.getPosition());
		setFillColor(copy.getFillColor());
		mode = copy.mode;
	}

	bool getMode()
	{
		return mode;
	}

	void switchMode()
	{
		if (mode)
		{
			mode = false;
		}
		else
		{
			mode = true;
		}
	}

private:
	bool mode;
};

class StartButton : public Button
{
public:
	StartButton(const Vector2f& pos = Vector2f(0, 0), const Vector2f& size = Vector2f(20, 20),
		const sf::Color& color = sf::Color::Green) : Button(pos, size, color)
	{

	}

	void onClick(int& round)
	{
		round++;
	}


};