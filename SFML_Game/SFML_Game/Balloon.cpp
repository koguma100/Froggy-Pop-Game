#include "Balloon.hpp"

Balloon::Balloon(const Balloon& copy)
{
    this->type = copy.type;
    this->color = copy.color;
    this->speed = copy.speed;
    this->direct = copy.direct;
    this->reachedEnd = copy.reachedEnd;
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

bool Balloon::getReachedEnd() const
{
    return reachedEnd;
}

void Balloon::setReachedEnd(bool reachedEnd)
{
    this->reachedEnd = reachedEnd;
}

void Balloon::moveBalloon(const vector<Checkpoint>& checkpoints, int& lives, int& eco)
{
    for (int i = 0; i < checkpoints.size(); ++i)
    {
        if (getGlobalBounds().intersects(checkpoints[i].getGlobalBounds()))
        {
            direct = checkpoints[i].getDirection();
        }
    }

    if (!reachedEnd && getPosition().y > 1000)
    {
        reachedEnd = true;
        lives -= type;
        eco += type;
        this->type = 0;
        cout << "Lives: " << lives << "   Eco: " << eco << endl;
    }

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

void spawnBalloon(int type, vector<Balloon*>& bloons)
{
    Balloon* temp = new Balloon(type, 20, Vector2f(-30, 360));

    bloons.push_back(temp);
}

void emptyBloons(vector<Balloon*>& bloons)
{
    while (bloons.size() > 0)
    {
        delete bloons.back();
        bloons.pop_back();
    }
}

bool roundEnded(vector<Balloon*>& bloons)
{
    bool ended = true;

    for (int i = 0; i < bloons.size() && ended == true; ++i)
    {
        if (bloons[i]->getType() != 0)
        {
            ended = false;
        }
    }
    return ended;
}
