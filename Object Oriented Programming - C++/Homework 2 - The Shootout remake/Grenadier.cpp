//
// Created by luana on 4/30/2020.
//

#include "Grenadier.h"
#include "Grenade.h"
Grenadier::Grenadier(pair<int, int> position, int health, int range, char type) : Character(position, health, range, type) {
    weapon = new Grenade;
    armor = new BulletproofVest;
}

Grenadier::~Grenadier(){
    delete weapon;
    delete armor;
}
