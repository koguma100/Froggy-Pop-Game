#include "Checkpoint.hpp"

class Bubble : public sf::Sprite {

public:

    Bubble(const Vector2f& position = Vector2f(0, 0), float degreeAngle = 0.0) : Sprite() {

        Vector2f size(0.25, 0.25);
        hitbox = sf::FloatRect(position, size);
        this->setPosition(position);
        active = true;
        movementX = cos((degreeAngle + 80) * 3.14159 / 180) * 2;
        movementY = sin((degreeAngle + 80) * 3.14159 / 180) * 2;
    }

    bool isActive();

    void setActive(bool isActive);

    void set_bubble_texture(sf::Texture& t);

    const vector<int>& getBloonsPopped();

    void move_bubble();

    void bloonHit(int bloonIndex);

private:
    bool active;
    float movementX,
          movementY;
    sf::FloatRect hitbox;
    sf::Texture image;
    vector<int> bloonsPopped;   // stores bloon indexes

};