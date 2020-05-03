//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_SNIPER_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_SNIPER_H


#include "Character.h"
#include <vector>

class Sniper : public Character {
public:
    Sniper(pair<int, int>, int health = 500, int range = 7, char type = 's');
    ~Sniper() override;

    void name() override;
};


#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_SNIPER_H
