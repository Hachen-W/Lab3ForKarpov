#ifndef LAIR_HPP_INCLUDED
#define LAIR_HPP_INCLUDED


#include <vector>
#include "entity.hpp"
#include "enemy.hpp"
#include "../table/table.hpp"


using std::vector;

typedef struct LairTableceil {
    unsigned int countStep;
    Enemy enemy;
} LairTableceil;

class Lair : public Entity {
private:
    Table<unsigned int, Enemy*> _table;
public:
    Lair(Table<unsigned int, Enemy*> table) : Entity(LairType) {
        _table = table;
    }
    Table<unsigned int, Enemy*> getTable() {
        return _table;
    }
    Enemy* update(unsigned int step) {
        unsigned int size = _table.getSize();
        for (int i = 0; i < size; i++) {
            if (step % _table.getElement(i).key == 0) {
                return new Enemy(*_table.getElement(i).value);
            }
        }
        throw std::logic_error("Undefined");
    }
    friend std::ostream& operator<<(std::ostream& output, Lair& obj) {
        unsigned int size = obj.getTable().getSize();
        for (int i = 0; i < size; i++) {
            TableCeil tableCeil = obj.getTable().getElement(i);
            cout << "Enemy " << i << endl;
            output << "Every Step: " << int(tableCeil.key) << endl << *(tableCeil.value);
        }
        return output;
    }
};


#endif