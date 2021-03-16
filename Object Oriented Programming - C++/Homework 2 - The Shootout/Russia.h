//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_RUSSIA_H
#define HOMEWORK_2___THE_SHOOTOUT_RUSSIA_H

#include "Player.h"
#include "Vodka.h"
#include "AK47.h"

class Russia : Player{
public:
    Russia(int Health = 3000, int Range = 5, AK47, Vodka, char type = 'R', bool effect = false);
    ~Russia();
};


#endif //HOMEWORK_2___THE_SHOOTOUT_RUSSIA_H
