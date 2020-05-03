//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_WEAPON_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_WEAPON_H

#include <iostream>
using namespace std;

class Weapon {
protected:
    int Damage;
public:
    Weapon(int damage = 50);
    virtual int getDamage() = 0;

    virtual void setAdrenaline(int);
    virtual void setHealth(int);
    virtual int getKillCount() const;
    virtual ~Weapon() = 0;
};


#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_WEAPON_H
