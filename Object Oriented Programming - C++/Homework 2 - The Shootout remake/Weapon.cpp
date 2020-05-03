//
// Created by luana on 4/30/2020.
//

#include "Weapon.h"

Weapon::Weapon(int damage) : Damage(damage){}

Weapon::~Weapon() {
    Damage = 0;
}

void Weapon::setAdrenaline(int) {}

void Weapon::setHealth(int) {}

int Weapon::getKillCount() const { return 0;}
