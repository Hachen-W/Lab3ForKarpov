#ifndef MAGICTOWER_HPP_INCLUDED
#define MAGICTOWER_HPP_INCLUDED


#include "tower.hpp"
#include "effect.hpp"


class MagicTower : public Tower {
private:
    Effect _effect;
public:
    MagicTower(Effect effect, double damage, unsigned int radius, unsigned int level) : Tower(damage, radius, level), _effect(effect) {
        setType(MagicTowerType);
    }
    Effect getEffect() {
        return _effect;
    }
    friend std::ostream& operator<<(std::ostream& output, MagicTower& obj) {
        output << "Damage: " << obj.getDamage() << endl;
        output << "Radius: " << obj.getRadius() << endl;
        output << "Level: " << obj.getLevel() << endl;
        output << obj.getEffect();
        return output;
    }
};


#endif