#include "Bubble.hpp"

class Balloon : public sf::CircleShape
{
public:
	Balloon(int type = 1, float size = 20, const sf::Vector2f& pos = sf::Vector2f(0, 0)) : CircleShape(size) {
        switch (type)
        {
        case 0:
            color = sf::Color::Transparent;
            speed = 10;
            break;
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
        case 4:
            color = sf::Color::Yellow;
            speed = 1.75;
            break; 
        default:
            color = sf::Color::Red;
            speed = 1;
        }

        this->type = type;
        this->reachedEnd = false;
        direct = RIGHT;
        this->setPosition(pos);
        this->setFillColor(color);
    };

	Balloon(const Balloon& copy);

	int getType() const;

	void setType(int type);

    void setDirection(direction direct);

    bool getReachedEnd() const;

    void setReachedEnd(bool reachedEnd);

    void moveBalloon(const vector<Checkpoint>& checkpoints, int& lives, int& eco);

    void bloonPop();

private:
	int type;
	direction direct;
	sf::Color color;
	float speed;
    bool reachedEnd;
};

typedef struct bloonWave
{
    int type,
        numOfBloons;
        vector<Balloon*>& bloons;
} BloonWave;

void spawnBalloon(int type, vector<Balloon*>& bloons);

void emptyBloons(vector<Balloon*>& bloons);

bool roundEnded(vector<Balloon*>& bloons);