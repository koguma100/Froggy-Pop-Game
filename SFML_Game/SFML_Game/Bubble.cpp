#include "Bubble.hpp"


void Bubble::move_bubble(float offsetX, float offsetY)
{
	this->move(offsetX,offsetY);
}

void Bubble::set_bubble_texture(sf::Texture &t)
{
	
	this->setTexture(t);
}
