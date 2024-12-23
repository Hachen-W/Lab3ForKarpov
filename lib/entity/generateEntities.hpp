#ifndef GENERATE_ENTITIES_HPP_INCLUDED
#define GENERATE_ENTITIES_HPP_INCLUDED


#include "../entity/tower.hpp"
#include "../entity/castle.hpp"
#include "../entity/enemy.hpp"
#include "../entity/lair.hpp"
#include "../entity/magicTrap.hpp"
#include "../entity/magicTower.hpp"


unsigned int COUNT_LAIRS = 5, GOLD_BY_DEFAULT = 0;
double HEALTH_BY_DEFAULT = 250.0;
// Tower
double TOWER_DAMAGE_DEFAULT = 10.0;
unsigned int TOWER_RADIUS_DEFAULT = 1;
unsigned int TOWER_LEVEL_DEFAULT = 1;
// Enemy
double ENEMY_DAMAGE_DEFAULT = 10.0;
unsigned int ENEMY_GOLD_DEFAULT = 100;
unsigned int ENEMY_SPEED_DEFAULT = 1;
double ENEMY_MAX_HEALTH = 10.0;
// Castle
double CASTLE_HEALTH_DEFAULT = 100.0;
unsigned int CASTLE_GOLD_DEFAULT = 50;
unsigned int CASTLE_GOLD_PER_GOLD = 50;
// Magic Trap
unsigned int MAGIC_TRAP_DAMAGE_DEFAULT = 5;
unsigned int MAGIC_TRAP_RADIUS_DEFAULT = 1;
unsigned int MAGIC_TRAP_TIME_DEFAULT = 1;
double MAGIC_TRAP_PERCENT_DEFAULT = 0.5;

class Generate {
public:
    Tower* generateTower() {
        return new Tower{TOWER_DAMAGE_DEFAULT, TOWER_RADIUS_DEFAULT, TOWER_LEVEL_DEFAULT};
    }
    Castle* generateCastle() {
        return new Castle(CASTLE_HEALTH_DEFAULT, CASTLE_GOLD_DEFAULT);
    }
    Enemy* generateEnemy() {
        return new Enemy(ENEMY_DAMAGE_DEFAULT,
                            ENEMY_GOLD_DEFAULT,
                            ENEMY_SPEED_DEFAULT,
                            ENEMY_MAX_HEALTH);
    }
    Entity* generateLair() {
        Table<unsigned int, Enemy*> table;
        TableCeil<unsigned int, Enemy*> tableCeil;
        tableCeil.key = 3;
        tableCeil.value = generateEnemy();
        table.push(tableCeil);
        return new Lair(table);
    }
    Effect generateEffect() {
        unsigned int effectTime = MAGIC_TRAP_TIME_DEFAULT;
        double effectPercent = MAGIC_TRAP_PERCENT_DEFAULT;
        unsigned int effectType;
        do {
            cout << "0. SlowDown" << endl;
            cout << "1. Poisoning" << endl;
            cout << "2. Weaking" << endl;
            cout << "Effect Type: " << endl;
            cin >> effectType;
        } while (effectType > 2);
        return Effect(EffectType(effectType), effectTime, effectPercent);
    }
    Entity* generateMagicTrap() {
        unsigned int damage = MAGIC_TRAP_DAMAGE_DEFAULT;
        unsigned int radius = MAGIC_TRAP_RADIUS_DEFAULT;
        Effect effect = generateEffect();
        return new MagicTrap(effect, radius);
    }
    Entity* generateMagicTower() {
        return new MagicTower(generateEffect(), TOWER_DAMAGE_DEFAULT, TOWER_RADIUS_DEFAULT, TOWER_LEVEL_DEFAULT);
    }
};


#endif