#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED


#include <iostream>

using std::cout;
using std::endl;


enum TypesEntities {
    CastleType = 0,
    TowerType,
    MagicTrapType,
    LairType,
    EnemyType,
    MagicTowerType,
};

class Entity {
private:
    TypesEntities _type;
public:
    Entity(unsigned int type) : _type(TypesEntities(type)) {}
    TypesEntities getType() {
        return _type;
    }
    void setType(TypesEntities type) {
        _type = type;
    }
};


#endif