//
// Created by luana on 4/30/2020.
//

#include "Rifle.h"

Rifle::Rifle(int damage) : Weapon(damage){}

int Rifle::getDamage() {
    //Every time a soldier shoots someone, his adrenaline is increased by one point
    //Adrenaline points increase the damage dealt by a soldier
    Adrenaline ++;
    return Damage + Adrenaline*0.5*Damage;
}

void Rifle::setAdrenaline(const int amount){
    Adrenaline = amount;
}

Rifle::~Rifle(){}