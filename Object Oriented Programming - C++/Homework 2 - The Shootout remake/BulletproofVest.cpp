//
// Created by luana on 4/30/2020.
//

#include "BulletproofVest.h"

BulletproofVest::BulletproofVest(int protection) : Protection(protection){}

int BulletproofVest::getProtection(){
    return Protection;
}

BulletproofVest::~BulletproofVest(){}

void BulletproofVest::decreaseDurability() {
    if(Durability > 0)
        Durability --;
}

int BulletproofVest::getDurability() {
    return Durability;
}


