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

    Character(pair<int, int>, int health = 0, int range = 0, char type = ' ');
    virtual ~Character() = 0;

    int getHealth();
    virtual void setHealth(int);
    int getRange();
    virtual int getDamage();
    int getProtection();
    virtual bool isDead();
    pair<int, int> getPosition();
    void changePosition(Map &, pair<int, int>);
    virtual void name() = 0;

    void winMessage();
    void positionMessage(pair<int, int>);
    void deadMessage();
    void killerMessage();
};

#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_CHARACTER_H
