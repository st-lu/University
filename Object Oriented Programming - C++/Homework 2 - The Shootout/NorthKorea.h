//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_NORTHKOREA_H
#define HOMEWORK_2___THE_SHOOTOUT_NORTHKOREA_H

#include "Player.h"
#include "Battlefield.h"
#include "NuclearBomb.h"
#include <climits>

class NorthKorea : Player {
public:
    NorthKorea(int Health = INT_MAX, int range = battlefieldSize, NuclearBomb, Armor, char type = 'K', bool effect = false);
    ~NorthKorea();

};


#endif //HOMEWORK_2___THE_SHOOTOUT_NORTHKOREA_H
