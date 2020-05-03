//
// Created by luana on 4/30/2020.
//

#include "Grenade.h"

Grenade::Grenade(int damage) : Weapon(damage){}
Grenade::~Grenade() {}

int Grenade::getDamage() {
    KillCount++;
    return Damage;
}

int Grenade::getKillCount() const {
    return KillCount;
}
