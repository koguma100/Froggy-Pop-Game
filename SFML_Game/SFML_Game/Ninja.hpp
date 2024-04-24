#include "DartFrog.hpp"


class NinjaFrog : public Tower {
public:
    NinjaFrog(const sf::Texture& texture, sf::Time newThrowSpeed, int pierce,
        float newSightRadius) :Tower(texture, newThrowSpeed, pierce, newSightRadius) {

    }
    NinjaFrog() : Tower()
    {

    }

    void shoot(vector<Balloon*>& bloons, sf::Texture& bubbleTexture, float& towerDegree)
    {
        if (getBloonInSight() != -1 && bloons[getBloonInSight()]->getType() != 0
            && checkInRadius(bloons[getBloonInSight()]->getPosition()))
        {
            towerDegree = findRotateDeg(bloons[getBloonInSight()]->getPosition());

            if (getElapsedTimeShoot() >= getThrowSpeed())
            {
                shootProjectile(towerDegree);
                getProjectiles()[getProjectiles().size() - 1].setTexture(bubbleTexture);
                shootProjectile(towerDegree + 30);
                getProjectiles()[getProjectiles().size() - 1].setTexture(bubbleTexture);
                shootProjectile(towerDegree - 30);
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
                    findRotateDeg(bloons[i]->getPosition());
                }
            }
        }
    }

};