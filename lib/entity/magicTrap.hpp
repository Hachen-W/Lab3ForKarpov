#ifndef MAGICTRAP_HPP_INCLUDED
#define MAGICTRAP_HPP_INCLUDED


#include "entity.hpp"
#include "effect.hpp"


class MagicTrap : public Entity {
private:
    Effect _effect;
    unsigned int _radius;
public:
    MagicTrap(Effect effect, unsigned int radius) : Entity(MagicTrapType), _effect(effect), _radius(radius) {}
    Effect getEffect() {
        return _effect;
    }
    unsigned int getRadius() {
        return _radius;
    }
    friend std::ostream& operator<<(std::ostream& output, MagicTrap& obj) {
        output << obj.getEffect();
        output << "Radius: " << obj.getRadius() << endl;
        return output;
    }
};


#endif