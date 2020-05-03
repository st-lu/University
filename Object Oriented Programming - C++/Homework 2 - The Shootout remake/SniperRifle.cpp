//
// Created by luana on 4/30/2020.
//

#include "SniperRifle.h"

SniperRifle::SniperRifle(int damage) : Weapon(damage){}

int SniperRifle::getDamage() {
    //snipers don't get any bonuses, they're already too powerful
    return Damage;
}

SniperRifle::~SniperRifle(){}