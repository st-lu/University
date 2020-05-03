//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_SNIPERRIFLE_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_SNIPERRIFLE_H

#include "Weapon.h"

class SniperRifle : public Weapon {
public:
    SniperRifle(int damage = 1000);
    ~SniperRifle();

    int getDamage();
};


#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_SNIPERRIFLE_H
