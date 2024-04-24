#include "Ninja.hpp"

class TackFrog : public Tower {


public:

    TackFrog(const sf::Texture& texture, sf::Time newThrowSpeed, int pierce,
        float newSightRadius) : Tower(texture, newThrowSpeed, pierce, newSightRadius) {


    };

    TackFrog() : Tower()
    {

    }


    void shoot(vector<Balloon*>& bloons, sf::Texture& bubbleTexture, float& towerDegree)
    {
        if (getBloonInSight() != -1 && bloons[getBloonInSight()]->getType() != 0
            && checkInRadius(bloons[getBloonInSight()]->getPosition()))
        {
            towerDegree = 0;

            if (getElapsedTimeShoot() >= getThrowSpeed())
            {
                shootProjectile(towerDegree);
                getProjectiles()[getProjectiles().size() - 1].setTexture(bubbleTexture);
                shootProjectile(towerDegree + 45);
                getProjectiles()[getProjectiles().size() - 1].setTexture(bubbleTexture);
                shootProjectile(towerDegree + 90);
                getProjectiles()[getProjectiles().size() - 1].setTexture(bubbleTexture);
                shootProjectile(towerDegree + 135);
                getProjectiles()[getProjectiles().size() - 1].setTexture(bubbleTexture);
                shootProjectile(towerDegree + 180);
                getProjectiles()[getProjectiles().size() - 1].setTexture(bubbleTexture);
                shootProjectile(towerDegree + 225);
                getProjectiles()[getProjectiles().size() - 1].setTexture(bubbleTexture);
                shootProjectile(towerDegree + 270);
                getProjectiles()[getProjectiles().size() - 1].setTexture(bubbleTexture);
                shootProjectile(towerDegree + 315);
                getProjectiles()[getProjectiles().size() - 1].setTexture(bubbleTexture);
                setElapsedTimeShoot(sf::milliseconds(0));
            }
        }
        else
        {
            setBloonInSight(-1);
            bool bloonFound = false;
            for (int i = 0; i < bloons.size() && !bloonFound; ++i)
            {
                if (checkInRadius(bloons[i]->getPosition()))
                {
                    bloonFound = true;
                    setBloonInSight(i);
                }
            }
        }
    }



};