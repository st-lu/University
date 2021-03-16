//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_PLAYER_H
#define HOMEWORK_2___THE_SHOOTOUT_PLAYER_H

#include "Weapon.h"
#include "Armor.h"

class Player {
protected:
    int Health;
    Weapon weapon;
    Armor armor;
    int Range;
    char type;
    bool effect;
public:
    Player(int Health = 1000, int Range = 5, Weapon, Armor, char, bool effect = false);
    virtual ~Player() = 0;

    int getHealth();
    void setHealth(int);
    int getRange();
    bool isDead();
    void changePosition();
    bool checkPosition();
    Position setTarget();
    Position nextPosition();
};


#endif //HOMEWORK_2___THE_SHOOTOUT_PLAYER_H
