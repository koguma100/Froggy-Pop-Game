#include "Balloon.hpp"

Balloon::Balloon(const Balloon& copy)
{
    this->type = copy.type;
    this->color = copy.color;
    this->speed = copy.speed;
    this->setPosition(copy.getPosition());
}

int Balloon::getType() const
{
    return type;
}

void Balloon::setType(int type)
{
    this->type = type;
}

void Balloon::moveBalloon()
{
    if (direct == UP)
    {
        this->move(0, speed * -1);
    }
    else if (direct == RIGHT)
    {
        this->move(speed, 0);
    }
    else if (direct == DOWN)
    {
        this->move(0, speed);
    }
    else if (direct == LEFT)
    {
        this->move(speed * -1, 0);
    }
}
