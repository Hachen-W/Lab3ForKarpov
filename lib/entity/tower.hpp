#ifndef TOWER_HPP_INCLUDED
#define TOWER_HPP_INCLUDED


#include "entity.hpp"


class Tower : public Entity {
private:
    double _damage;
    unsigned int _radius;
    unsigned int _level;
public:
    Tower(double damage, unsigned int radius, unsigned int level) : Entity(TowerType), _damage(damage), _radius(radius), _level(level) {}
    double getDamage() {
        return _damage;
    }
    void setDamage(double damage) {
        _damage = damage;
    }
    unsigned int getRadius() {
        return _radius;
    }
    void setRadius(unsigned int radius) {
        _radius = radius;
    }
    unsigned int getLevel() {
        return _level;
    }
    void setLevel(unsigned int level) {
        _level = level;
    }
    void upgrade() {
        setDamage(getDamage() * 1.1);
        setLevel(getLevel() + 1);
    }
    friend std::ostream& operator<<(std::ostream& output, Tower& obj) {
        output << "Damage: " << obj.getDamage() << endl;
        output << "Radius: " << obj.getRadius() << endl;
        output << "Level: " << obj.getLevel() << endl;
        return output;
    }
};


#endif