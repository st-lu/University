//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_SOLDIER_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_SOLDIER_H

#include "Character.h"

class Soldier : public Character {
public:
    Soldier(pair<int, int>, int health = 300, int range = 4, char type = 'p');
    ~Soldier();
};


#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_SOLDIER_H
