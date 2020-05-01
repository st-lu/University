//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_SPY_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_SPY_H

#include "Character.h"
using namespace std;

class Spy : public Character{
public:
    Spy(pair<int, int>, int health = 500, int range = 7, char type = 's');
    ~Spy();
};


#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_SPY_H
