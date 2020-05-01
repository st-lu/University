//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_GRENADE_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_GRENADE_H

#include "Weapon.h"

class Grenade : public Weapon {
public:
    Grenade(int damage = 1000);
    ~Grenade();
};


#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_GRENADE_H
