//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_CHARACTER_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_CHARACTER_H


#include <iostream>
#include "Map.h"
#include "Weapon.h"
#include "BulletproofVest.h"
using namespace std;
class Character {
protected:
    int Health;
    int Range;
    pair<int, int> Position;
    char Type;
    Weapon *weapon;
    BulletproofVest *armor;
public:

    Character(pair<int, int>, int health = 100, int range = 3, char type = '0');
    virtual ~Character() = 0;

    int getHealth();
    void setHealth(int);
    int getRange();
    int getDamage();
    int getProtection();
    virtual bool isDead();
    pair<int, int> getPosition();
    char getType();
    void changePosition(Map &, pair<int, int>);
    pair<int, int> findTarget(Map&);
};

#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_CHARACTER_H
