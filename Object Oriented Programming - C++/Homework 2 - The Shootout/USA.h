//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_USA_H
#define HOMEWORK_2___THE_SHOOTOUT_USA_H

#include "Player.h"
#include "BulletproofVest.h"
#include "AK47.h"

class USA : Player {
public:
    USA(int Health = 4000, int Range = 4, AK47, BulletproofVest, char type = 'U', bool effect = false);
    ~USA();
};


#endif //HOMEWORK_2___THE_SHOOTOUT_USA_H
