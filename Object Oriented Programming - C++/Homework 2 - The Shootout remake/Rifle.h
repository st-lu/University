//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_RIFLE_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_RIFLE_H

#include "Weapon.h"

class Rifle : public Weapon {
protected:
    int Adrenaline = 0;
    //only characters with this type of weapons have adrenaline bonus
    //only soldiers have this type of weapon
public:
    Rifle(int damage = 150);

    int getDamage() override;
    void setAdrenaline(int) override;

    ~Rifle() override;
};


#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_RIFLE_H
