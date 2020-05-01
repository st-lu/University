//
// Created by luana on 4/30/2020.
//

#ifndef HOMEWORK_2___THE_SHOOTOUT_REMAKE_GRENADIER_H
#define HOMEWORK_2___THE_SHOOTOUT_REMAKE_GRENADIER_H

#include "Character.h"
using namespace std;

class Grenadier : public Character{
public:
    Grenadier(pair<int, int>, int health = 300, int range = 4, char type = 's');
    ~Grenadier();
};

#endif //HOMEWORK_2___THE_SHOOTOUT_REMAKE_GRENADIER_H
