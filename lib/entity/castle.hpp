#ifndef CASTLE_HPP_INCLUDED
#define CASTLE_HPP_INCLUDED


#include <string>
#include "entity.hpp"

using std::string;


class Castle : public Entity {
private:
    double _curHealth;
    double _maxHealth;
    unsigned int _gold;
public:
    Castle(double health, unsigned int gold) : _curHealth(health), _maxHealth(health), _gold(gold), Entity(CastleType) {}
    double getCurHealth() {
        return _curHealth;
    }
    double getMaxHealth() {
        return _maxHealth;
    }
    void setCurHealth(double health) {
        _curHealth = health;
    }
    unsigned int getGold() {
        return _gold;
    }
    void setGold(unsigned int gold) {
        _gold = gold;
    }
    friend std::ostream& operator<<(std::ostream& output, Castle& obj) {
        output << "Current Health: " << obj.getCurHealth() << endl;
        output << "Maximum Health: " << obj.getMaxHealth() << endl;
        output << "Gold: " << obj.getGold() << endl;
        return output;
    }
};


#endif