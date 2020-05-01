//
// Created by luana on 4/30/2020.
//

#include "Weapon.h"

Weapon::Weapon(int damage) : Damage(damage){}

int Weapon::getDamage() {
    return Damage;
}

Weapon::~Weapon() {
    Damage = 0;
}