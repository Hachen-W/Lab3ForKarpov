#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED


#include <vector>
#include <string>
#include "entity.hpp"
#include "effect.hpp"

using std::string;
using std::vector;




class Enemy : public Entity {
private:
    double _damage;
    unsigned int _gold;
    unsigned int _speed;
    double _curHealth;
    double _maxHealth;
    vector<Effect> _effects;
public:
    Enemy(unsigned int damage, unsigned int gold, unsigned int speed, double maxHealth) : Entity(EnemyType) {
        _damage = damage;
        _gold = gold;
        _speed = speed;
        _curHealth = maxHealth;
        _maxHealth = maxHealth;
    }
    double getDamage() {
        return _damage;
    }
    void setDamage(double damage) {
        _damage = damage;
    }
    unsigned int getGold() {
        return _gold;
    }
    void setGold(unsigned int gold) {
        _gold = gold;
    }
    unsigned int getSpeed() {
        return _speed;
    }
    void setSpeed(unsigned int speed) {
        _speed = speed;
    }
    double getCurHealth() {
        return _curHealth;
    }
    void setCurHealth(double curHealth) {
        _curHealth = curHealth;
    }
    double getMaxHealth() {
        return _maxHealth;
    }
    void setMaxHealth(double maxHealth) {
        _maxHealth = maxHealth;
    }
    vector<Effect> getEffects() {
        return _effects;
    }
    void pushback(Effect effect) {
        _effects.push_back(effect);
    }
    friend std::ostream& operator<<(std::ostream& output, Enemy& obj) {
        output << "Damage: " << obj.getDamage() << endl;
        output << "Gold: " << obj.getGold() << endl;
        output << "Speed: " << obj.getSpeed() << endl;
        output << "Current Health: " << obj.getCurHealth() << endl;
        output << "Maximum Health: " << obj.getMaxHealth() << endl;
        for (Effect effect : obj._effects) {
            output << effect;
        }
        return output;
    }
};


#endif