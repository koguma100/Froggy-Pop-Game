#include "Checkpoint.hpp"

class Bubble :public sf::Sprite {

public:

    Bubble(const Vector2f& position = Vector2f(0, 0)) :Sprite() {

        Vector2f size(0.25, 0.25);
        hitbox = sf::FloatRect(position, size);
        this->setPosition(position);
    }


    void move_bubble(float offsetX, float offsetY);
    void set_bubble_texture(sf::Texture& t);

private:


    sf::FloatRect hitbox;
    sf::Texture image;

};