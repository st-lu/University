//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_NUCLEARBOMB_H
#define HOMEWORK_2___THE_SHOOTOUT_NUCLEARBOMB_H

#include "Weapon.h"

class NuclearBomb : Weapon {
public:
    NuclearBomb(int damage = 5000);
    bool GameOver(){return true;};
    ~NuclearBomb();

};


#endif //HOMEWORK_2___THE_SHOOTOUT_NUCLEARBOMB_H
