#include "Bubble.hpp"


void Bubble::move_bubble()
{
    this->move(movementX, movementY);
}

bool Bubble::isActive()
{
    return active;
}

void Bubble::setActive(bool isActive)
{
    active = isActive;
}

void Bubble::set_bubble_texture(sf::Texture& t)
{

    this->setTexture(t);
}

const vector<int>& Bubble::getBloonsPopped()
{
    return bloonsPopped;
}

void Bubble::bloonHit(int bloonIndex)
{
    bloonsPopped.push_back(bloonIndex);
}
