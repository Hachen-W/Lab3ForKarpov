#ifndef LANDSCAPE_HPP_INCLUDED
#define LANDSCAPE_HPP_INCLUDED


#include <iostream>
#include <vector>
#include "../matrix/matrix_new.hpp"
#include "../table/table.hpp"
#include "../entity/entity.hpp"
#include "../entity/castle.hpp"
#include "../entity/lair.hpp"

using std::pair;
using std::vector;



enum LandscapeType {
    Road = 0,
    Field,
    Forest,
};

/*
typedef struct TableCeil {
    pair<unsigned int, unsigned int> point;
    Entity* entity;
} TableCeil;
*/

class Landscape {
private:
    Matrix<LandscapeType> _playground;
    TableChain<pair<unsigned int, unsigned int>, Entity*> _table;
public:
    Matrix<LandscapeType>& getPlayground() {
        return _playground;
    }
    TableChain<pair<unsigned int, unsigned int>, Entity*>& getTable() {
        return _table;
    }
};


#endif