#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED


#include <iostream>
#include <vector>
#include <string>
#include "../landscape/landscape.hpp"
#include "../entity/castle.hpp"
#include "../entity/tower.hpp"
#include "../menu/menu.hpp"
#include "../entity/generateEntities.hpp"
#include "../entity/magicTrap.hpp"


using std::cout;
using std::endl;
using std::string;
using std::vector;

unsigned int TOWER_COST = 600;
unsigned int MAGIC_TRAP_COST = 100;
unsigned int MAGIC_TOWER_COST = 750;
unsigned int IMPROVE_TOWER_COST = 150;
unsigned int IMPROVE_MAGIC_TOWER_COST = 250;
unsigned int GOLD_DEFAULT = 500;

/**
 * \brief Class Game releasing Tower Defence
 * \param landscape
 * \param _menu Menu with that player works
 * \param _path Path alnog that enemies go
 * \param _castle
 * \param _lair
 * \param _countSteps
 * \param _gold
 */
class Game : public Generate {
private:
    Landscape landscape;
    Menu _menu;
    vector<pair<unsigned int, unsigned int>> _path;
    TableCeil<pair<unsigned int, unsigned int>, Castle*> _castle;
    TableCeil<pair<unsigned int, unsigned int>, Lair*> _lair;
    unsigned int _countSteps;
    unsigned int _gold;
public:
    /**
     * \brief Constructor for game
     * \details In the beginning count of steps = 0
     * 
     */
    Game() : _gold(GOLD_DEFAULT), _countSteps(0) {
        vector<string> menu;
        menu.push_back("0. Next Move");
        menu.push_back("1. Build Tower");
        menu.push_back("2. Build Magic Trap");
        menu.push_back("3. Build Magic Tower");
        menu.push_back("4. Improve Tower");
        menu.push_back("5. Improve Magic Tower");
        _menu.setMenu(menu);
    }
    friend std::ostream& operator<<(std::ostream& output, Game& obj) {
        TableCeil<pair<unsigned int, unsigned int>, vector<Entity*>> tableCeils;
        unsigned int size;
        output << "Game" << endl;
        output << "Gold: " << obj.getGold() << endl;
        output << "Count Step: " << obj.getCountSteps() << endl;
        for (unsigned int i = 0; i < obj.landscape.getPlayground().getStringsCount(); i++) {
            for (unsigned int j = 0; j < obj.landscape.getPlayground().getColumnsCount(); j++)
                output << int(obj.landscape.getPlayground().get(i, j));
            output << endl;
        }
        output << "(" << obj._castle.key.first << "; " << obj._castle.key.second << ")" << " - ";
        output << "Castle" << endl;
        output << *obj._castle.value;
        output << "(" << obj._lair.key.first << "; " << obj._lair.key.second << ")" << " - ";
        output << "Lair" << endl;
        output << *obj._lair.value;

        for (int i = 0; i < obj.landscape.getTable().getSize(); i++) {
            tableCeils = obj.landscape.getTable().getElement(i);
            size = tableCeils.value.size();
            
            for (unsigned int j = 0; j < size; j++) {
                output << "(" << tableCeils.key.first << "; " << tableCeils.key.second << ")" << " - ";
                switch (tableCeils.value[j]->getType()) {
                    case EnemyType:
                        output << "Enemy" << endl;
                        output << *static_cast<Enemy*>(tableCeils.value[j]);
                        break;
                    case CastleType:
                        output << "Castle" << endl;
                        output << *static_cast<Castle*>(tableCeils.value[j]);
                        break;
                    case TowerType:
                        output << "Tower" << endl;
                        output << *static_cast<Tower*>(tableCeils.value[j]);
                        break;
                    case MagicTrapType:
                        output << "Magic Trap" << endl;
                        output << *static_cast<MagicTrap*>(tableCeils.value[j]);
                        break;
                    case LairType:
                        output << "Lair" << endl;
                        output << *static_cast<Lair*>(tableCeils.value[j]);
                        break;
                    case MagicTowerType:
                        output << "Magic Tower" << endl;
                        output << *static_cast<MagicTower*>(tableCeils.value[j]);
                        break;
                }
            }
        }
        cout << "Path" << endl;
        for (pair<unsigned int, unsigned int> point : obj._path)
            cout << point.first << " " << point.second << endl;
        return output;
    }
    double enemyEffect(Enemy* enemy, EffectType effect) {
        double percentSum = 0;
        vector<Effect> effects = enemy->getEffects();
        vector<Effect> effectsNew;
        unsigned int sizeEffects = effects.size();
        for (unsigned int i = 0; i < sizeEffects; i++) {
            if (effects.at(i).getType() == effect) {
                percentSum += effects.at(i).getPercent();
                effects.at(i).setTime(effects.at(i).getTime() - 1);
            }
            if (effects.at(i).getTime() > 1) {
                effectsNew.push_back(effects.at(i));
            }
        }
        return percentSum;
    }
    /**
     * @param countStrings count strings in playground's matrix
     * @param countColumns count columns in playground's matrix
     * @details 
     *  - Generate Landscape
     *  - Add Castle and Lair
     *  - Add Roads Between Castle and Lair
     */
    void generatePlayground(unsigned int countStrings, unsigned int countColumns) {
        // Initialization
        pair<unsigned int, unsigned int> pointCeilCastle, pointCeilLair;
        std::vector<TableCeil<pair<unsigned int, unsigned int>, Entity*>> tableCeils;
        TableCeil<pair<unsigned int, unsigned int>, Entity*> tableCeil;

        // Landscape
        generateLandscape(countStrings, countColumns);

        // Castle
        _castle.key = generatePoint(countStrings, countColumns);
        _castle.value = static_cast<Castle*>(generateCastle());
        srand(time(NULL));
        // Lair
        do {
            _lair.key.first = rand() % countStrings;
            _lair.key.second = rand() % countColumns;
        } while (_lair.key.first == _castle.key.first &&
                    _lair.key.second == _lair.key.second);
        _lair.value = static_cast<Lair*>(generateLair());

        // Road
        pointCeilCastle = _castle.key;
        pointCeilLair = _lair.key;

        for (unsigned int i = 0; i <= abs((int) pointCeilCastle.second - (int) pointCeilLair.second); i++) {
            if (pointCeilCastle.second < pointCeilLair.second) {
                landscape.getPlayground().get(pointCeilCastle.first, pointCeilCastle.second + i) = Road;
                _path.push_back({pointCeilCastle.first, pointCeilCastle.second + i});
            }
            else {
                landscape.getPlayground().get(pointCeilCastle.first, pointCeilCastle.second - i) = Road;
                _path.push_back({pointCeilCastle.first, pointCeilCastle.second - i});
            }
        }
        for (unsigned int i = 1; i <= abs((int) pointCeilCastle.first - (int) pointCeilLair.first); i++) {
            if (pointCeilCastle.first < pointCeilLair.first) {
                landscape.getPlayground().get(pointCeilCastle.first + i, pointCeilLair.second) = Road;
                _path.push_back({pointCeilCastle.first + i, pointCeilLair.second});
            }
            else {
                landscape.getPlayground().get(pointCeilCastle.first - i, pointCeilLair.second) = Road;
                _path.push_back({pointCeilCastle.first - i, pointCeilLair.second});
            }
        }
        _path.erase(_path.begin());
        _path.erase(_path.end());
        landscape.getPlayground().get(pointCeilCastle.first, pointCeilCastle.second) = Field;
        landscape.getPlayground().get(pointCeilLair.first, pointCeilLair.second) = Field;
    }
    void generateLandscape(unsigned int countStrings, unsigned int countColumns) {
        landscape.getPlayground().resize(countStrings, countColumns);
        for (unsigned int i = 0; i < countStrings; i++)
            for (unsigned int j = 0; j < countColumns; j++)
                landscape.getPlayground().get(i, j) = Forest;
    }
    pair<unsigned int, unsigned int> generatePoint(unsigned int limitFirst, unsigned int limitSecond) {
        srand(time(NULL));
        pair<unsigned int, unsigned int> point;
        do {
            try {
                point.first = rand() % limitFirst;
                point.second = rand() % limitSecond;
                landscape.getTable().getElement(point);
            } catch (std::logic_error& err) {
                return point;
            }
        } while (true);
    }

    /**
     * @details
     *  - Enemy Make a Step
     *  - Player Make a Step
     */
    void makeStep() {
        unsigned int size = landscape.getTable().getSize();
        TableCeil<pair<unsigned int, unsigned int>, vector<Entity*>> tableCeils;
        TableCeil<pair<unsigned int, unsigned int>, Entity*> tableCeil;
        unsigned int sizeVector;
        TableChain<pair<unsigned int, unsigned int>, Entity*> tableTemp;

        movePlayer(_castle.value, tableTemp);
        updateCastle();
        moveLair({_lair.key, (Entity*) _lair.value}, tableTemp);

        for (int index = 0; index < size; index++) {
            tableCeils = landscape.getTable().getElement(index); // Потоки, замеры
            sizeVector = tableCeils.value.size();
            for (int j = 0; j < sizeVector; j++) {
                tableCeil.key = tableCeils.key;
                tableCeil.value = tableCeils.value[j];
                switch (tableCeils.value[j]->getType()) {
                    case TowerType:
                        moveTower(tableCeil, tableTemp);
                        break;
                    case MagicTrapType:
                        cout << "Here!" << endl;
                        moveMagicTrap(tableCeil, tableTemp);
                        break;
                    case EnemyType:
                        moveEnemy(tableCeil, tableTemp);
                        break;
                    case MagicTowerType:
                        moveMagicTower(tableCeil, tableTemp);
                        break;
                }
            }
        }
        landscape.getTable() = tableTemp;
        _countSteps++;
    }
    void updateCastle() {
        setGold(getGold() + _castle.value->getGold());
    }
    void moveTower(TableCeil<pair<unsigned int, unsigned int>, Entity*> tableCeil, TableChain<pair<unsigned int, unsigned int>, Entity*>& tableTemp) {
        vector<Entity*> valueTemp;
        unsigned int size;
        Tower* tower = static_cast<Tower*>(tableCeil.value);
        pair<unsigned int, unsigned int> point = tableCeil.key;
        pair<unsigned int, unsigned int> temp = {0, 0};
        int radius = tower->getRadius();
        for (int j = -radius; j <= radius; j++) {
            for (int k = -radius; k <= radius; k++) {
                temp.first = point.first + j;
                temp.second = point.second + k;

                if (0 <= temp.first && temp.first < landscape.getPlayground().getStringsCount() && 
                        0 <= temp.second && temp.second < landscape.getPlayground().getColumnsCount()) {
                    try {
                        valueTemp = landscape.getTable().getElement(temp);
                        size = valueTemp.size();
                        for (unsigned int j = 0; j < size; j++) {
                            if (valueTemp[j]->getType() == EnemyType) {
                                Enemy* enemy = static_cast<Enemy*>(valueTemp[j]);
                                enemy->setCurHealth(enemy->getCurHealth() - tower->getDamage());
                            }
                        }
                    } catch(std::logic_error& err) {}
                }
            }
        }
        tableTemp.push(tableCeil);
    }
    void moveMagicTrap(TableCeil<pair<unsigned int, unsigned int>, Entity*> tableCeil, TableChain<pair<unsigned int, unsigned int>, Entity*>& tableTemp) {
        vector<Entity*> valueTemp;
        unsigned int size;

        MagicTrap* magicTrap = static_cast<MagicTrap*>(tableCeil.value);
        pair<unsigned int, unsigned int> point = tableCeil.key;
        pair<unsigned int, unsigned int> temp = {0, 0};
        int radius = magicTrap->getRadius();
        bool flag = false;

        for (int j = -radius; j <= radius; j++) {
            for (int k = -radius; k <= radius; k++) {
                temp.first = point.first + j;
                temp.second = point.second + k;

                if (0 <= temp.first && temp.first < landscape.getPlayground().getStringsCount() && 
                        0 <= temp.second && temp.second < landscape.getPlayground().getColumnsCount()) {
                    try {
                        valueTemp = landscape.getTable().getElement(temp);
                        size = valueTemp.size();
                        for (unsigned int j = 0; j < size; j++) {
                            if (valueTemp[j]->getType() == EnemyType) {
                                Enemy* enemy = static_cast<Enemy*>(valueTemp[j]);
                                enemy->pushback(magicTrap->getEffect());
                                flag = true;
                            }
                        }
                    } catch(std::logic_error& err) {}
                }
            }
        }
        if (!flag)
            tableTemp.push(tableCeil);
        else
            delete magicTrap;
    }
    void moveLair(TableCeil<pair<unsigned int, unsigned int>, Entity*> tableCeil, TableChain<pair<unsigned int, unsigned int>, Entity*>& tableTemp) {
        Lair* temp = static_cast<Lair*>(tableCeil.value);
        try {
            TableCeil<pair<unsigned int, unsigned int>, Entity*> tempTableCeil;
            Enemy* enemy = temp->update(_countSteps);
            tempTableCeil.key = _path.at(_path.size() - 1);
            tempTableCeil.value = enemy;
            tableTemp.push(tempTableCeil);
        } catch (std::logic_error err) {}
    }
    void moveMagicTower(TableCeil<pair<unsigned int, unsigned int>, Entity*> tableCeil, TableChain<pair<unsigned int, unsigned int>, Entity*>& tableTemp) {
        vector<Entity*> valueTemp;
        unsigned int size;

        MagicTower* magicTower = static_cast<MagicTower*>(tableCeil.value);
        pair<unsigned int, unsigned int> point = tableCeil.key;
        pair<unsigned int, unsigned int> temp = {0, 0};
        int radius = magicTower->getRadius();
        for (int j = -radius; j <= radius; j++) {
            for (int k = -radius; k <= radius; k++) {
                temp.first = point.first + j;
                temp.second = point.second + k;
                if (0 <= temp.first && temp.first < landscape.getPlayground().getStringsCount() && 
                        0 <= temp.second && temp.second < landscape.getPlayground().getColumnsCount()) {
                    try {
                        valueTemp = landscape.getTable().getElement(temp);
                        size = valueTemp.size();
                        for (unsigned int j = 0; j < size; j++) {
                            if (valueTemp[j]->getType() == EnemyType) {
                                Enemy* enemy = static_cast<Enemy*>(valueTemp[j]);
                                enemy->setCurHealth(enemy->getCurHealth() - magicTower->getDamage());
                                enemy->pushback(magicTower->getEffect());
                            }
                        }
                    } catch(std::logic_error& err) {}
                }
            }
        }
        tableTemp.push(tableCeil);
    }
    void moveEnemy(TableCeil<pair<unsigned int, unsigned int>, Entity*> tableCeil, TableChain<pair<unsigned int, unsigned int>, Entity*>& tableTemp)  {
        Enemy* temp = static_cast<Enemy*>(tableCeil.value);
        unsigned int count = 0;
        unsigned int speed = ((double) temp->getSpeed()) * (1 - enemyEffect(temp, SLOWDOWN));
        if (temp->getCurHealth() > 0)
            for (unsigned int j = _path.size() - 1; j >= 0 && speed - count > 0; j--) {
                if (j == 0) {
                    enemyAttack(_castle.value, temp);
                    delete temp;
                    break;
                }
                if (_path.at(j).first == tableCeil.key.first && _path.at(j).second == tableCeil.key.second) {
                    tableCeil.key = _path.at(j - 1);
                    double newHealth = ((double) temp->getCurHealth()) * (1.0 - enemyEffect(temp, POISONING)) ;
                    temp->setCurHealth(newHealth);
                    try {
                        tableTemp.push(tableCeil);
                    } catch (std::logic_error& err) {}
                    count++;
                }
            }
        else {
            setGold(getGold() + temp->getGold());
            delete temp;
        }
    }
    void enemyAttack(Castle* castle, Enemy* enemy) {
        castle->setCurHealth(castle->getCurHealth() - enemy->getDamage() * (1 - enemyEffect(enemy, WEAKENING)));
    }
    void movePlayer(Castle* castle, TableChain<pair<unsigned int, unsigned int>, Entity*>& tableTemp) {
        if (castle->getCurHealth() <= 0) {
            cout << "Defeat" << endl;
            return;
        }
        unsigned int string, column;
        unsigned int option;
        while ((option = _menu.dialog()) != 0) {
            switch (option) 
            {
                case 0:
                    return;
                case 1:
                {
                    if (getGold() < TOWER_COST) {
                        cout << "Not Enough Money" << endl;
                        continue;
                    }
                    setGold(getGold() - TOWER_COST);
                    Entity* tower = generateTower();
                    do {
                        cout << "Tower String: ";
                        cin >> string;
                        cout << "Tower Column: ";
                        cin >> column;
                    } while ((string >= landscape.getPlayground().getStringsCount() ||
                                column >= landscape.getPlayground().getColumnsCount()) && 
                                landscape.getPlayground().get(string, column) != Field);
                    tableTemp.push({{string, column}, tower});
                    break;
                }
                case 2:
                {
                    if (getGold() < MAGIC_TRAP_COST) {
                        cout << "Not Enough Money" << endl;
                        continue;
                    }
                    setGold(getGold() - MAGIC_TRAP_COST);

                    Entity* trap = generateMagicTrap();
                    do {
                        cout << "Trap String: ";
                        cin >> string;
                        cout << "Trap Column: ";
                        cin >> column;
                    } while ((string >= landscape.getPlayground().getStringsCount() ||
                                column >= landscape.getPlayground().getColumnsCount()) && 
                                landscape.getPlayground().get(string, column) == Road);
                    tableTemp.push({{string, column}, trap});
                    break;
                }
                case 3:
                {
                    if (getGold() < MAGIC_TOWER_COST) {
                        cout << "Not Enough Money" << endl;
                        continue;
                    }
                    setGold(getGold() - MAGIC_TOWER_COST);

                    Entity* magicTower = generateMagicTower();
                    do {
                        cout << "Magic Tower String: ";
                        cin >> string;
                        cout << "Magic Tower Column: ";
                        cin >> column;
                    } while ((string >= landscape.getPlayground().getStringsCount() ||
                                column >= landscape.getPlayground().getColumnsCount()) && 
                                landscape.getPlayground().get(string, column) != Field);
                    tableTemp.push({{string, column}, magicTower});
                    break;
                }
                case 4:
                {
                    if (getGold() < IMPROVE_TOWER_COST) {
                        cout << "Not Enough Money" << endl;
                        continue;
                    }
                    setGold(getGold() - IMPROVE_TOWER_COST);
                    bool flag = true;
                    do {
                        cout << "Magic Tower String: ";
                        cin >> string;
                        cout << "Magic Tower Column: ";
                        cin >> column;
                        flag = checkTower(string, column);
                    } while ((string >= landscape.getPlayground().getStringsCount() ||
                                column >= landscape.getPlayground().getColumnsCount()) && 
                                flag);
                    improveTower(string, column);
                    break;
                }
                case 5:
                {
                    if (getGold() < IMPROVE_MAGIC_TOWER_COST) {
                        cout << "Not Enough Money" << endl;
                        continue;
                    }
                    setGold(getGold() - IMPROVE_MAGIC_TOWER_COST);
                    bool flag = true;
                    do {
                        cout << "Magic Trap String: ";
                        cin >> string;
                        cout << "Magic Trap Column: ";
                        cin >> column;
                        flag = checkMagicTower(string, column);
                    } while ((string >= landscape.getPlayground().getStringsCount() ||
                                column >= landscape.getPlayground().getColumnsCount()) && 
                                flag);
                    improveMagicTower(string, column);
                    break;
                }
            }
        }
    }
    bool checkTower(unsigned int string, unsigned int column) {
        try {
            vector<Entity*> values = landscape.getTable().getElement({string, column});
            unsigned int sizeValues = values.size();
            for (unsigned int i = 0; i < sizeValues; i++) {
                if (values[i]->getType() == TowerType)
                    return true;
            }
            return false;
        } catch (std::logic_error& err) {
            cout << err.what() << endl;
            return false;
        }
    }
    void improveTower(unsigned int string, unsigned int column) {
        try {
            vector<Entity*> values = landscape.getTable().getElement({string, column});
            unsigned int sizeValues = values.size();
            for (unsigned int i = 0; i < sizeValues; i++) {
                if (values[i]->getType() == TowerType) {
                    Tower* value = static_cast<Tower*>(values[i]);
                    value->upgrade();
                    return;
                }
            }
        } catch (std::logic_error& err) {
            cout << err.what() << endl;
        }
    }
    bool checkMagicTower(unsigned int string, unsigned int column) {
        try {
            vector<Entity*> values = landscape.getTable().getElement({string, column});
            unsigned int sizeValues = values.size();
            for (unsigned int i = 0; i < sizeValues; i++) {
                if (values[i]->getType() == TowerType)
                    return true;
            }
            return false;
        } catch(std::logic_error& err) {
            cout << err.what() << endl;
            return false;
        }
    }
    void improveMagicTower(unsigned int string, unsigned int column) {
        try{
            vector<Entity*> values = landscape.getTable().getElement({string, column});
            unsigned int sizeValues = values.size();
            for (unsigned int i = 0; i < sizeValues; i++) {
                if (values[i]->getType() == TowerType) {
                    Tower* value = static_cast<Tower*>(values[i]);
                    value->upgrade();
                    return;
                }
            }
        } catch(std::logic_error& err) {
            cout << err.what() << endl;
        }
    }
    unsigned int getCountSteps() {
        return _countSteps;
    }
    void setCountSteps(unsigned int countStep) {
        _countSteps = countStep;
    }
    unsigned int getGold() {
        return _gold;
    }
    void setGold(unsigned int gold) {
        _gold = gold;
    }
    ~Game() {
        unsigned int size = landscape.getTable().getSize();
        unsigned int sizeVector;
        for (unsigned int i = 0; i < size; i++) {
            sizeVector =landscape.getTable().getElement(i).value.size();
            for (unsigned int j = 0; j < sizeVector; j++)
                delete landscape.getTable().getElement(i).value[j];
        }
    }
};


#endif