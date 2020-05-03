//
// Created by luana on 4/30/2020.
//

#include "Sniper.h"
#include "SniperRifle.h"
Sniper::Sniper(pair<int, int> position, int health, int range, char type) : Character(position, health, range) {
    weapon = new SniperRifle;
    armor = new BulletproofVest;
}

void Sniper::name(){
    cout << "Sniper";
}

Sniper::~Sniper(){
    delete weapon;
    delete armor;
}

